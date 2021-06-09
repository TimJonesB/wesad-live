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
                                     [&ctx](){return Server<Wrist_BVP.Nchannels>(ctx, Wrist_BVP).run();});
    return 0;
}
