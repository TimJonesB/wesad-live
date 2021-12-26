/** @file */
#ifndef PROCESSORH
#define PROCESSORH

#include <vector>
#include <map>
#include <array>

#include <armadillo>

#include "client.h"
#include "data_config.h"
#include "realtime/Detectors.h"

/** 
 * @brief Continously loops through DataQueue's and processes data.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * 
 * Continously inspects all DataQueues, pop's data off if available, and processes according to algorithms being used. 
 */

template <size_t ConfigIndex>
class ProcBuf {
public:
    ProcBuf() {
        buf.zeros();
        hrbuf.zeros();
    }

    ~ProcBuf() = default;

    template <typename T>
    ProcBuf& insert(T val) {
        buf.row(index % ProcBufLen) = arma::rowvec(std::vector<double> (val.begin(), val.end()));
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

    int ecg(double val) {
        int fs = 700;
        auto res = ecg_det.processSample(val); 
        if (res != -1) {
            return 1;
        }
        return 0;
    }

    int hr() {
        return 0;     
    }

    auto dom_fq(size_t fs) {
        arma::vec fft_res = arma::abs(arma::fft(buf)/buf.size());
        arma::vec fft_res_1side = fft_res(arma::span(0, buf.size()/2)) * 2;
        arma::vec f_fft = arma::linspace(0, fs, buf.size());
        arma::vec f_fft1 = f_fft(arma::span(0, (buf.size()/2)));
        auto fft_sort = arma::sort_index(fft_res_1side, "descend");
        arma::vec  fq_ranked = f_fft1(fft_sort);
        double result = fq_ranked(0) != 0 ? fq_ranked(0) : fq_ranked(1);
        return result;
    }

    void print() {
        std::cout << "Index " << ConfigIndex << " buf:\n" << buf << std::endl;
    }
     
private:

    void inc_index() {
        index = (index < ProcBufLen - 1) ? index + 1 : 0;
    }

    arma::mat::fixed<ProcBufLen, ConfigList[ConfigIndex].Nchannels> buf;
    arma::vec::fixed<HeartBeatBufLen> hrbuf;
    size_t hr_interval = 0;

    DetectorPanTompkins ecg_det = DetectorPanTompkins(700);
    int index = 0;

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
private:
    int calc_feature(std::array<double, ConfigList[ConfigIndex].Nchannels> arr,
                     std::array<double, NumberOfFeatures> &state );
    ProcBuf<ConfigIndex> pbuff;
    QueueMgr<ConfigIndex> q;
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

inline void print_state(std::array<double, NumberOfFeatures> &state) {
    std::cout << "Proc State:"  << std::endl;
    for (auto it : state) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
}

template<size_t ConfigIndex>
inline int FeatureProcessor<ConfigIndex>::calc_feature(std::array<double, ConfigList[ConfigIndex].Nchannels> arr, std::array<double, NumberOfFeatures> &state) {
    pbuff.insert(arr);
    pbuff.print();

    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/ACC") { //Chest Acc
        state[0] = pbuff.mean();
        state[1] = pbuff.stddev();
        // TODO: placeholders for x,y,z component features
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/ECG") { //Chest Acc
        state[2] = pbuff.mean(); //mean hr
        state[3] = pbuff.stddev(); //std hr
        state[4] = pbuff.mean(); //mean hrv
        state[5] = pbuff.stddev(); //std hrv
        //TODO: change to actual hr, hrv
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/EMG") { //Chest Acc
        is_hb = pbuff.ecg();
        state[6] = pbuff.mean(); //mean
        state[7] = pbuff.stddev(); //std 
        state[8] = pbuff.dom_fq(); //fq
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/EDA") { //Chest Acc
        state[9] = pbuff.mean(); //mean
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/Temp") { //Chest Acc
        state[10] = pbuff.mean(); //mean
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/chest/Resp") { //Chest Acc
        // state[i] = pbuff.mean(); //mean
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/wrist/ACC") { //Chest Acc
        state[11] = pbuff.mean(); //mean
        state[12] = pbuff.max(); //mean
        state[13] = pbuff.min(); //mean
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/wrist/BVP") { //Chest Acc
        state[14] = pbuff.mean(); //mean hr
        state[15] = pbuff.stddev(); //std hr
        state[16] = pbuff.mean(); //mean hrv
        state[17] = pbuff.stddev(); //std hrv
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/wrist/EDA") { //Chest Acc
        state[18] = pbuff.mean(); //mean hr
    }
    if constexpr (ConfigList[ConfigIndex].path == "/signal/wrist/TEMP") { //Chest Acc
        state[19] = pbuff.mean(); //mean hr
    }
    print_state(state);
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
            calc_feature(arr, state);
            // std::cout << " from " << ConfigList[ConfigIndex].path  << std::endl;
        }
        else {
            // std::cout << "Waiting on " <<  ConfigList[ConfigIndex].path << " data" << std::endl;
        }
    }

    return 0;
}












#endif //PROCESSORH
