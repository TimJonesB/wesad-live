#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "server.h"
#include "h5_data.h"
#include "publisher.h"
#include "h5_sandbox.h"


Server::Server(std::string name, zmq::context_t &ctx) :
        name{name},
        publisher {ctx, Config::ports.at(name)},
        data {H5Data("../data/S2.h5")}
    {}


int Server::run() {
    int i = 0;
    std::cout << "Running " << this->name << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    int dt_us = int(1e6/Config::fs.at(this->name));
    std::cout << "dt microsecs: " << dt_us << std::endl;
    while(i<3000) {
        double d = 0.0;
        if (!this->name.empty()) {
            d = this->data.read_point<double>(this->name, i);
        }
        else {
            d = -1.0;
        }
        auto res = this->publisher.send(d);
        std::this_thread::sleep_for(std::chrono::microseconds(dt_us));
        i++;
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(finish-start);
    std::cout << this->name << " finished in " << secs.count() << " seconds."  << std::endl;
    return 0;
}