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
    std::future<int> f0 = std::async(std::launch::async, [&ctx](){return Server<0>(ctx).run();});
    std::future<int> f1 = std::async(std::launch::async, [&ctx](){return Server<1>(ctx).run();});
    std::future<int> f2 = std::async(std::launch::async, [&ctx](){return Server<2>(ctx).run();});
    std::future<int> f3 = std::async(std::launch::async, [&ctx](){return Server<3>(ctx).run();});
    std::future<int> f4 = std::async(std::launch::async, [&ctx](){return Server<4>(ctx).run();});
    std::future<int> f5 = std::async(std::launch::async, [&ctx](){return Server<5>(ctx).run();});
    std::future<int> f6 = std::async(std::launch::async, [&ctx](){return Server<6>(ctx).run();});
    std::future<int> f7 = std::async(std::launch::async, [&ctx](){return Server<7>(ctx).run();});
    std::future<int> f8 = std::async(std::launch::async, [&ctx](){return Server<8>(ctx).run();});
    std::future<int> f9 = std::async(std::launch::async, [&ctx](){return Server<9>(ctx).run();});
    return 0;
}
