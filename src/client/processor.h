/** @file */
#ifndef PROCESSORH
#define PROCESSORH

#include <vector>
#include <map>
#include <array>

#include <armadillo>
#include <boost/circular_buffer.hpp>

#include "client.h"
#include "data_config.h"
#include "realtime/Detectors.h"

/** 
 * @brief Continously loops through DataQueue's and processes data.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * 
 * Continously inspects all DataQueues, pop's data off if available, and processes according to algorithms being used. 
 */

inline void print_state(std::array<double, NumberOfFeatures> &state) {
    std::cout << "Proc State:"  << std::endl;
    for (size_t i = 0; i < NumberOfFeatures; i++) {
        std::cout << i << ": " << state[i] << std::endl;
    }
    std::cout << std::endl;
}

template <size_t ConfigIndex>
class HeartBeatBuf {
public:

    template <typename T>
    HeartBeatBuf& insert(T val) {
        beat_interval_steps++;
        size_t ins_val = 0;
        if (is_hbeat(val)) {
            ins_val = beat_interval_steps;
            beat_interval_steps = 0;
        }
        buf.push_back(ins_val);
        return *this;
    }


    double hr_mean() {
        arma::vec hr = get_hr_vec();
        return arma::mean(hr);
    }

    double hr_std() {
        arma::vec hr = get_hr_vec();
        return arma::stddev(hr);
    }

    double hrv_std() {
        arma::vec intervals (get_beat_intervals());
        for (size_t i = 0; i < intervals.size(); i ++) {
            intervals(i) = to_ms(intervals(i));
        }
        double std = intervals.empty() ? 0.0 : arma::stddev(intervals);
        return std;
    }

    double hrv_mean() {
        arma::vec intervals(get_beat_intervals());
        for (size_t i = 0; i < intervals.size(); i ++) {
            intervals(i) = to_ms(intervals(i));
        }
        double mean = intervals.empty() ? 0.0 : arma::mean(intervals);
        return mean;
    }

private:

    int is_hbeat(double val) {
        auto res = ecg_det.processSample(val); 
        if (res != -1) {
            return 1;
        }
        return 0;
    }

    double to_ms (size_t beat_interval) {
        double dt = (1/double(ConfigList[ConfigIndex].fs)); // seconds
        return dt * beat_interval * 1000; // ms
    }

    std::vector<double> get_beat_intervals() {
        std::vector<double> intervals;
        for (auto it : buf ) {
            if (it > 0) {
                intervals.push_back(it);
            }
        }
        return intervals; // average beat intervals in ms
    }

    arma::vec get_hr_vec () { 
        std::vector<double> intervals = get_beat_intervals(); 
        if (intervals.size() < 2) {
            return arma::vec({0});
        }
        arma::vec ints(intervals);
        arma::vec hr = ConfigList[ConfigIndex].fs * (60 / (ints));
        arma::vec mean_filt (hr_moving_avg_window, arma::fill::none);
        mean_filt.fill(1.0 / hr_moving_avg_window);
        arma::vec mv_avg = arma::conv(hr, mean_filt);
        return mv_avg;
    }

    boost::circular_buffer<size_t> buf{ConfigList[ConfigIndex].buf_size};
    DetectorPanTompkins ecg_det = DetectorPanTompkins(ConfigList[ConfigIndex].fs);
    size_t beat_interval_steps = 0; ///Steps since last heartbeat;
    size_t index = 0;
};    


template <size_t ConfigIndex>
class ProcBuf {
public:
    ProcBuf() {
        buf.zeros();
    }

    ~ProcBuf() = default;

    template <typename T>
    ProcBuf& insert(T val) {
        buf.row(index % ConfigList[ConfigIndex].buf_size) = arma::rowvec(std::vector<double> (val.begin(), 
                                                                                              val.end()));
        if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/ECG" || ConfigList[ConfigIndex].path == "/signal/wrist/BVP") {
            hb_buf.insert(val[0]);
        }
        inc_index();
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &out, const ProcBuf &rhs){
        out << rhs.buf;
        return out;
    }

    auto mean() { 

        return arma::mean(buf);
    }

    auto stddev() {
        return arma::stddev(buf);
    }

    auto max() {
        return arma::max(buf);
    }

    auto min() {
        return arma::min(buf);
    }

    auto dyn_range() {
        return arma::range(buf);
    }

    auto hr_mean() {
        return hb_buf.hr_mean();
    }

    auto hr_std() {
        return hb_buf.hr_std();
    }

    auto hrv_mean() {
        return hb_buf.hrv_mean();
    }

    auto hrv_std() {
        return hb_buf.hrv_std();
    }

    auto dom_fq() {
        arma::vec fft_res = arma::abs(arma::fft(buf)/buf.size());
        arma::vec fft_res_1side = fft_res(arma::span(0, buf.size()/2)) * 2;
        arma::vec f_fft = arma::linspace(0, ConfigList[ConfigIndex].fs, buf.size());
        arma::vec f_fft1 = f_fft(arma::span(0, (buf.size()/2)));
        auto fft_sort = arma::sort_index(fft_res_1side, "descend");
        arma::vec fq_ranked = f_fft1(fft_sort);
        double result = fq_ranked(0) != 0 ? fq_ranked(0) : fq_ranked(1);
        return result;
    }

    void print() {
        std::cout << "Index " << ConfigIndex << " buf:\n" << buf << std::endl;
    }

    arma::vec col(size_t index) {
        return buf.col(index);
    }
     
private:

    void inc_index() {
        index = (index < ConfigList[ConfigIndex].buf_size - 1) ? index + 1 : 0;
    }
    arma::mat::fixed<ConfigList[ConfigIndex].buf_size, 
                     ConfigList[ConfigIndex].Nchannels> buf; /// Holds moving-window data for all statistical measurements
    HeartBeatBuf<ConfigIndex> hb_buf;
    size_t index = 0;
};



class Processor {
public:
    int run();
private:
    template <size_t CurrentIndex>
    int init_feature_procs(std::vector<std::future<int>> &v);
    std::array<double, NumberOfFeatures> state;
};


template<size_t ConfigIndex>
class FeatureProcessor{
public:
    int run(std::array<double, NumberOfFeatures> &state);
    int process(std::array<double, ConfigList[ConfigIndex].Nchannels> arr, 
                std::array<double, NumberOfFeatures> &state);
private:
    QueueMgr<ConfigIndex> q; /// Gets the data
    ProcBuf<ConfigIndex> pbuff; /// Stores the data for processing
    int calc_feature(std::array<double, ConfigList[ConfigIndex].Nchannels> arr,
                     std::array<double, NumberOfFeatures> &state ); /// Processes the data
};

/** 
 * @brief Continously calls proc_all_feats.
 * 
 * Continously calls proc_all_feats which loops through DataQueue's and processes data.
 * @returns Runs indefinitely
 */
inline int Processor::run() {
    std::vector<std::future<int>> v;
    init_feature_procs<std::size(ConfigList)-1>(v);
    while(1) {
        if (print_state_bool) {
            std::this_thread::sleep_for(std::chrono::milliseconds(print_state_delay_ms));
            print_state(state);
        }
    }
    return 0;
}


/** 
 * @brief TMP method recursively calls proc_q<CurrentIndex>, proc_q<CurrentIndex-1>.
 * @tparam CurrentIndex Index of the DataQueue in ClientQueues::.
 * 
 * TMP method recursively calls proc_q<CurrentIndex>, proc_q<CurrentIndex-1> size(ConfigList) times.
 * @returns 0
 */
template<size_t CurrentIndex>
inline int Processor::init_feature_procs(std::vector<std::future<int>> &v){
    if constexpr (CurrentIndex+1){
        if constexpr (ConfigList[CurrentIndex].status == Cfg::ACTIVE) {
            v.push_back(std::async(std::launch::async, [this](){return FeatureProcessor<CurrentIndex>().run(this->state);}));
        }
        return init_feature_procs<CurrentIndex-1>(v);
    }
    else {
        return 0;
    }
}

template<size_t ConfigIndex>
inline int FeatureProcessor<ConfigIndex>::process(std::array<double, ConfigList[ConfigIndex].Nchannels> arr, std::array<double, NumberOfFeatures> &state) {
    pbuff.insert(arr);
    calc_feature(arr, state);
    return 0;
}

template<size_t ConfigIndex>
inline int FeatureProcessor<ConfigIndex>::calc_feature(std::array<double, ConfigList[ConfigIndex].Nchannels> arr, std::array<double, NumberOfFeatures> &state) {
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/ACC") { //Chest Acc
        arma::vec x = pbuff.col(0);
        arma::vec y = pbuff.col(1);
        arma::vec z = pbuff.col(2);
        double xmean = arma::mean(x);
        double ymean = arma::mean(y);
        double zmean = arma::mean(z);
        double xstd = arma::stddev(x);
        double ystd = arma::stddev(y);
        double zstd = arma::stddev(z);
        double acc_mean = xmean + ymean + zmean;
        double acc_std = xstd + ystd + zstd;
        state[0] = acc_mean;
        state[1] = acc_std;
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/ECG") { //Chest Acc
        state[2] = pbuff.hr_mean(); //mean hr
        state[3] = pbuff.hr_std(); //std hr
        state[4] = pbuff.hrv_mean(); //mean hrv
        state[5] = pbuff.hrv_std(); //std hrv
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/EMG") { //Chest Acc
        // is_hb = pbuff.ecg();
        state[6] = pbuff.mean(); //mean
        state[7] = pbuff.stddev(); //std 
        state[8] = pbuff.dom_fq(); //fq
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/EDA") { //Chest Acc
        state[9] = pbuff.mean(); //mean
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/Temp") { //Chest Acc
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/Resp") { //Chest Acc
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/wrist/ACC") { //Chest Acc
        arma::vec x = pbuff.col(0);
        arma::vec y = pbuff.col(1);
        arma::vec z = pbuff.col(2);
        double xmean = arma::mean(x);
        double ymean = arma::mean(y);
        double zmean = arma::mean(z);
        double xstd = arma::stddev(x);
        double ystd = arma::stddev(y);
        double zstd = arma::stddev(z);
        double xmax = arma::max(x);
        double ymax = arma::max(y);
        double zmax = arma::max(z);
        double xmin = arma::min(x);
        double ymin = arma::min(y);
        double zmin = arma::min(z);
        double acc_mean = xmean + ymean + zmean;
        double std_mean = xstd + ystd + zstd;
        double acc_min  = xmean + ymean + zmean;
        double acc_std = xstd + ystd + zstd;
        state[10] = xmean;
        state[11] = xmax;
        state[12] = xmin;

    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/wrist/BVP") { //Chest Acc
        state[13] = pbuff.hr_mean(); //mean hr
        state[14] = pbuff.hr_std(); //std hr
        state[15] = pbuff.hrv_mean(); //mean hrv
        state[16] = pbuff.hrv_std(); //std hrv
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/wrist/EDA") { //Chest Acc
        state[17] = pbuff.mean(); //mean hr
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/wrist/TEMP") { //Chest Acc
        state[18] = pbuff.mean(); //mean hr
    }
    return 0;
}


/** 
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * 
 * Processes DataQueue at ConfigIndex by popping data from Queue and providing to processor.
 * @returns 0
 */
template <size_t ConfigIndex>
inline int FeatureProcessor<ConfigIndex>::run(std::array<double, NumberOfFeatures> &state) {
    std::cout << "Running FeatureProcessor Index " << ConfigIndex << std::endl;
    std::array<double, ConfigList[ConfigIndex].Nchannels> arr;
    while(1) {
        if (!q.empty()) {
            q.pop(arr); // pop top of q and put into arr memory
            // std::cout << "popped :";
            // for (int i = 0; i < arr.size(); i++) {
            //     std::cout << " " << arr[i];
            // }
            process(arr, state);
            // std::cout << " from " << ConfigList[ConfigIndex].path  << std::endl;
        }
        else {
            // std::cout << "Waiting on " <<  ConfigList[ConfigIndex].path << " data" << std::endl;
        }
    }

    return 0;
}


#endif //PROCESSORH
