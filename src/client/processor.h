#ifndef PROCESSORH
#define PROCESSORH

#include <deque>
#include <vector>
#include <map>
#include <array>


#include "client.h"
#include "data_config.h"

class Processor {

public:
    int run();
private:
    template <size_t Nchannels>
    int proc_q(Config cfg, boost::lockfree::spsc_queue<std::array<double, Nchannels>> &q);
};

int Processor::run() {
    while(1) {
        proc_q(Chest_ACC, Chest_ACC_q);
        proc_q(Chest_ECG, Chest_ECG_q);
        proc_q(Chest_EMG, Chest_EMG_q);
        proc_q(Chest_EDA, Chest_EDA_q);
        proc_q(Chest_RESP, Chest_RESP_q);
        proc_q(Wrist_ACC, Wrist_ACC_q);
        proc_q(Wrist_BVP, Wrist_BVP_q);
        proc_q(Wrist_EDA, Wrist_EDA_q);
        proc_q(Wrist_TEMP, Wrist_TEMP_q);
    }
    return 0;
}


template <size_t Nchannels>
int Processor::proc_q(Config cfg, boost::lockfree::spsc_queue<std::array<double, Nchannels>> &q) {
    if (!q.empty()) {
        std::array<double, Nchannels> arr;
        q.pop(arr);
        std::cout << "popped :";
        for (int i = 0; i < arr.size(); i++) {
            std::cout << " " << arr[i];
        }
        std::cout << " from " << cfg.path  << std::endl;

    }
    else {
        // std::cout << "Waiting on " <<  cfg.path << " data" << std::endl;
    }

    return 0;
}


#endif //PROCESSORH