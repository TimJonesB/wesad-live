#ifndef PROCESSORH
#define PROCESSORH

#include <vector>
#include <map>
#include <array>

#include "client.h"
#include "data_config.h"


class Processor {
public:
    int run();
private:
    template <size_t ConfigIndex>
    int proc_q(boost::lockfree::spsc_queue<std::array<double, ConfigList[ConfigIndex].Nchannels>> &q);
};


int Processor::run() {
    while(1) {
        proc_q<0>(q0);
        proc_q<1>(q1);
        proc_q<2>(q2);
        proc_q<3>(q3);
        proc_q<4>(q4);
        proc_q<5>(q5);
        proc_q<6>(q6);
        proc_q<7>(q7);
        proc_q<8>(q8);
        proc_q<9>(q9);
    }
    return 0;
}


template <size_t ConfigIndex>
int Processor::proc_q(boost::lockfree::spsc_queue<std::array<double, ConfigList[ConfigIndex].Nchannels>> &q) {
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


#endif //PROCESSORH
