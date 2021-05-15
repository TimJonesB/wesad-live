#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "server.h"
#include "h5_data.h"
#include "publisher.h"


Server::Server(std::string name, zmq::context_t &ctx, const std::string tcp_port) :
        name{name},
        publisher {ctx, tcp_port},
        data {H5Data("../data/outfile.h5")}
    {}


int Server::run() {

    int i = 0;
    if (this->name == "server0") {
        i = 100000;
    }
    if (this->name == "server1") {
        std::cout << "yep!" << std::endl;
        i = 200000;
    }
    if (this->name == "server2") {
        i = 300000;
    }
    while(i<400000) {

        int d = this->data.read_point("label", i);
        d = i;
        zmq::message_t msg(std::to_string(d));
        std::cout << this->name << " sending message: " << msg.to_string() << std::endl;
        auto res = this->publisher.pub.send(msg, zmq::send_flags::none);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        i++;
    }
    return 0;
}