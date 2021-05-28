#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include "server.h"


int main() {
    zmq::context_t ctx;
    std::future<int> f0 = std::async(std::launch::async,
                                     [&ctx](){return Server("/signal/chest/EMG", ctx).run();});
    std::future<int> f1 = std::async(std::launch::async,
                                     [&ctx](){return Server("/signal/wrist/EDA", ctx).run();});
    std::future<int> f2 = std::async(std::launch::async,
                                     [&ctx](){return Server("/signal/wrist/ACC", ctx).run();});
    return 0;
}
