/** @file */
#ifndef PROCESSORH
#define PROCESSORH

#include <vector>
#include <map>
#include <array>

#include <armadillo>

#include "client.h"
#include "data_config.h"

/** 
 * @brief Continously loops through DataQueue's and processes data.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * 
 * Continously inspects all DataQueues, pop's data off if available, and processes according to algorithms being used. 
 */
class Processor {
public:
    int run();
private:
    template <size_t ConfigIndex>
    int proc_q();
    template <size_t CurrentIndex>
    int proc_all_q();

};


/** 
 * @brief Continously calls proc_all_q.
 * 
 * Continously calls proc_all_q which loops through DataQueue's and processes data.
 * @returns Runs indefinitely
 */
inline int Processor::run() {
    while(1) {
        proc_all_q<std::size(ConfigList)-1>();
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
inline int Processor::proc_all_q(){
    proc_q<CurrentIndex>();
    if constexpr (CurrentIndex) {
        return proc_all_q<CurrentIndex-1>();
    }
    else {
        return 0;
    }
}


/** 
 * @brief Processes DataQueue at ConfigIndex
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * 
 * Processes DataQueue at ConfigIndex by popping data from Queue and providing to processor.
 * @returns 0
 */
template <size_t ConfigIndex>
inline int Processor::proc_q() {
    QueueMgr<ConfigIndex> q;
    if (!q.empty()) {
        std::array<double, ConfigList[ConfigIndex].Nchannels> arr;
        q.pop(arr);
        std::cout << "popped :";
        for (int i = 0; i < arr.size(); i++) {
            std::cout << " " << arr[i];
        }
        std::cout << " from " << ConfigList[ConfigIndex].path  << std::endl;

    }
    else {
        // std::cout << "Waiting on " <<  ConfigList[ConfigIndex].path << " data" << std::endl;
    }

    return 0;
}


class ProcBuf {
public:

    ProcBuf() {
        buf.zeros();
    }

    ~ProcBuf() = default;

    template <typename T>
    ProcBuf& insert(T val) {
        buf(index % ProcBufLen) = val;
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

private:

    void inc_index() {
        index = (index < ProcBufLen - 1) ? index + 1 : 0;
    }

    arma::vec::fixed<ProcBufLen> buf;
    int index = 0;

};










#endif //PROCESSORH
