#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>

#include "server.h"
#include "config.h"


int main() {
    zmq::context_t ctx;
    // std::future<int> f0 = std::async(std::launch::async,
    //                                  [&ctx](){return Server<Chest_EMG.Nchannels>(Chest_EMG, ctx).run();});
    std::future<int> f1 = std::async(std::launch::async,
                                     [&ctx](){return Server<Wrist_ACC.Nchannels>(Wrist_ACC, ctx).run();});
    // std::future<int> f2 = std::async(std::launch::async,
    //                                  [&ctx](){return Server("/signal/wrist/ACC", ctx).run();});
    return 0;
}
