#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "H5Cpp.h"
#include "client.h"

Client::Client(zmq::context_t &ctx, const std::string tcp_portsm) : subscriber {ctx, tcp_portsm} {}

int Client::run() {
    while(1) {
        zmq::message_t msgs;
        auto res = this->subscriber.sub.recv(msgs, zmq::recv_flags::none);
        // std::cout << "Received: " << msgs.to_string() << std::endl;
    }
}
