#include <zmq.hpp>
#include <iostream>
#include <string>
#include "H5Cpp.h"
#include "client.h"
#include <thread>
#include <chrono>

int main() {
    zmq::context_t ctx;
    zmq::socket_t sub(ctx, ZMQ_SUB);
    const std::string addr = "tcp://127.0.0.1:5555";
    sub.connect(addr);
    sub.setsockopt(ZMQ_SUBSCRIBE, "", 0); // need to est. initial msg filter, because everything is filtered by default...

    std::this_thread::sleep_for(std::chrono::seconds(2));
    while(1) {
        //  Pass by reference
        zmq::message_t msgs;
        auto res = sub.recv(msgs, zmq::recv_flags::none);
        std::cout << "Received: " << msgs.to_string() << std::endl;
    }
    return 0;
}