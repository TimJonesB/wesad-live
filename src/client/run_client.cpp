#include <zmq.hpp>
#include <thread>
#include <chrono>
#include <future>


#include "client.h"
#include "data_config.h"
#include "processor.h"

int main() {
    zmq::context_t ctx;
    std::future<int> f0 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_ACC.Nchannels>(ctx, Chest_ACC, Chest_ACC_q).run();});
    std::future<int> f1 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_ECG.Nchannels>(ctx, Chest_ECG, Chest_ECG_q).run();});
    std::future<int> f2 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_EMG.Nchannels>(ctx, Chest_EMG, Chest_EMG_q).run();});
    std::future<int> f3 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_EDA.Nchannels>(ctx, Chest_EDA, Chest_EDA_q).run();});
    // // std::future<int> f4 = std::async(std::launch::async,
    // //                                  [&ctx](){return Client<Chest_TEMP.Nchannels>(ctx, Chest_TEMP, Chest_TEMP_q).run();});
    std::future<int> f5 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_RESP.Nchannels>(ctx, Chest_RESP, Chest_RESP_q).run();});
    std::future<int> f6 = std::async(std::launch::async,
                                     [&ctx](){return Client<Wrist_ACC.Nchannels>(ctx, Wrist_ACC, Wrist_ACC_q).run();});
    std::future<int> f7 = std::async(std::launch::async,
                                     [&ctx](){return Client<Wrist_BVP.Nchannels>(ctx, Wrist_BVP, Wrist_BVP_q).run();});
    std::future<int> f8 = std::async(std::launch::async,
                                     [&ctx](){return Client<Wrist_EDA.Nchannels>(ctx, Wrist_EDA, Wrist_BVP_q).run();});
    std::future<int> f9 = std::async(std::launch::async,
                                     [&ctx](){return Client<Wrist_TEMP.Nchannels>(ctx, Wrist_TEMP, Wrist_BVP_q).run();});
    Processor p;
    p.run();
    return 0;
}
