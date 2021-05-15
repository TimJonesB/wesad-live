#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include "server.h"


const std::string tcp_port0{"tcp://127.0.0.1:5000"};
const std::string tcp_port1{"tcp://127.0.0.1:5001"};
const std::string tcp_port2{"tcp://127.0.0.1:5002"};

int main() {
    zmq::context_t ctx;
    std::future<int> f0 = std::async(std::launch::async,
                                     [&ctx](){return Server("server0", ctx, tcp_port0).run();});
    std::future<int> f1 = std::async(std::launch::async,
                                     [&ctx](){return Server("server1", ctx, tcp_port1).run();});
    std::future<int> f2 = std::async(std::launch::async,
                                     [&ctx](){return Server("server2", ctx, tcp_port2).run();});
    return 0;
}
