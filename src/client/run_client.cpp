#include <zmq.hpp>
#include <thread>
#include <chrono>
#include <future>


#include "client.h"
#include "data_config.h"
#include "processor.h"

int main() {
    zmq::context_t ctx;
    Processor P{};
    P.Chest_ACC_q; 
    std::future<int> f0 = std::async(std::launch::async,
                                     [&ctx, &(P.Chest_ACC_q)](){return Client<Chest_ACC.Nchannels>(ctx, Chest_ACC).run();});
    std::future<int> f1 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_ECG.Nchannels>(ctx, Chest_ECG).run();});
    std::future<int> f2 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_EMG.Nchannels>(ctx, Chest_EMG).run();});
    std::future<int> f3 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_EDA.Nchannels>(ctx, Chest_EDA).run();});
    // std::future<int> f4 = std::async(std::launch::async,
    //                                  [&ctx](){return Client<Chest_TEMP.Nchannels>(ctx, Chest_TEMP).run();});
    std::future<int> f5 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_RESP.Nchannels>(ctx, Chest_RESP).run();});
    std::future<int> f6 = std::async(std::launch::async,
                                     [&ctx](){return Client<Wrist_ACC.Nchannels>(ctx, Wrist_ACC).run();});
    std::future<int> f7 = std::async(std::launch::async,
                                     [&ctx](){return Client<Wrist_BVP.Nchannels>(ctx, Wrist_BVP).run();});
    std::future<int> f8 = std::async(std::launch::async,
                                     [&ctx](){return Client<Wrist_EDA.Nchannels>(ctx, Wrist_EDA).run();});
    std::future<int> f9 = std::async(std::launch::async,
                                     [&ctx](){return Client<Wrist_TEMP.Nchannels>(ctx, Wrist_TEMP).run();});
    return 0;
}
