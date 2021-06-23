#ifndef PROCESSORH
#define PROCESSORH

#include <deque>
#include <vector>
#include <map>
#include <array>

#include <boost/lockfree/queue.hpp>

#include "client.h"
#include "data_config.h"

class Processor {

public:
    int i = 1;
    boost::lockfree::queue<std::array<double, Chest_ACC.Nchannels>> Chest_ACC_q {data_queue_sz};
    boost::lockfree::queue<std::array<double, Chest_ECG.Nchannels>> Chest_ECG_q {data_queue_sz};
    boost::lockfree::queue<std::array<double, Chest_EMG.Nchannels>> Chest_EMG_q {data_queue_sz};
    boost::lockfree::queue<std::array<double, Chest_EDA.Nchannels>> Chest_EDA_q {data_queue_sz};
    // boost::lockfree::queue<std::array<double, Chest_TEMP.Nchannels>> Chest_TEMP_q {data_queue_sz};
    boost::lockfree::queue<std::array<double, Chest_RESP.Nchannels>> Chest_RESP_q {data_queue_sz};
    boost::lockfree::queue<std::array<double, Wrist_ACC.Nchannels>> Wrist_ACC_q {data_queue_sz};
    boost::lockfree::queue<std::array<double, Wrist_BVP.Nchannels>> Wrist_BVP_q {data_queue_sz};
    boost::lockfree::queue<std::array<double, Wrist_EDA.Nchannels>> Wrist_EDA_q {data_queue_sz};
    boost::lockfree::queue<std::array<double, Wrist_TEMP.Nchannels>> Wrist_TEMP_q {data_queue_sz};
};


#endif //PROCESSORH