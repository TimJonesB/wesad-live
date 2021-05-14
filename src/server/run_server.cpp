#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include "H5Cpp.h"
#include "server.h"
#include "h5_data.h"


const std::string tcp_port0{"tcp://127.0.0.1:5000"};
const std::string tcp_port1{"tcp://127.0.0.1:5001"};

int main() {
    zmq::context_t ctx;
    std::future<int> f0 = std::async(std::launch::async,
                                     [&ctx](){return Server(ctx, tcp_port0).run();});
    std::future<int> f1 = std::async(std::launch::async,
                                     [&ctx](){return Server(ctx, tcp_port1).run();});
    return 0;
}
