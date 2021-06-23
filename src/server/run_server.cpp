#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>

#include "server.h"
#include "data_config.h"


int main() {
    zmq::context_t ctx;
    std::future<int> f0 = std::async(std::launch::async,
                                     [&ctx](){return Server<Chest_ACC.Nchannels>(ctx, Chest_ACC).run();});
    std::future<int> f1 = std::async(std::launch::async,
                                     [&ctx](){return Server<Chest_ECG.Nchannels>(ctx, Chest_ECG).run();});
    std::future<int> f2 = std::async(std::launch::async,
                                     [&ctx](){return Server<Chest_EMG.Nchannels>(ctx, Chest_EMG).run();});
    std::future<int> f3 = std::async(std::launch::async,
                                     [&ctx](){return Server<Chest_EDA.Nchannels>(ctx, Chest_EDA).run();});
    // std::future<int> f4 = std::async(std::launch::async,
    //                                  [&ctx](){return Server<Chest_TEMP.Nchannels>(ctx, Chest_TEMP).run();});
    std::future<int> f5 = std::async(std::launch::async,
                                     [&ctx](){return Server<Chest_RESP.Nchannels>(ctx, Chest_RESP).run();});
    std::future<int> f6 = std::async(std::launch::async,
                                     [&ctx](){return Server<Wrist_ACC.Nchannels>(ctx, Wrist_ACC).run();});
    std::future<int> f7 = std::async(std::launch::async,
                                     [&ctx](){return Server<Wrist_BVP.Nchannels>(ctx, Wrist_BVP).run();});
    std::future<int> f8 = std::async(std::launch::async,
                                     [&ctx](){return Server<Wrist_EDA.Nchannels>(ctx, Wrist_EDA).run();});
    std::future<int> f9 = std::async(std::launch::async,
                                     [&ctx](){return Server<Wrist_TEMP.Nchannels>(ctx, Wrist_TEMP).run();});
    return 0;
}
