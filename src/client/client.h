#ifndef CLIENTH
#define CLIENTH

#include <iostream>
#include <array>
#include <deque>
#include "subscriber.h"
#include "data_config.h"

template <size_t Nchannels>
class Client {

public:
    Client() = delete;
    Client(zmq::context_t &ctx, Config cfg);
    ~Client() = default;

    int run();
private:
    Subscriber subscriber;
    Config cfg;
    std::deque<std::array<double, Nchannels>> dq;
};

template <size_t Nchannels>
Client<Nchannels>::Client(zmq::context_t &ctx, Config cfg) :
        subscriber {ctx, std::string(cfg.port)},
        cfg{cfg} {}

template <size_t Nchannels>
int Client<Nchannels>::run() {
    while(1) {
        std::array<double, Nchannels> recv_buf;
        auto res = this->subscriber.sub.recv(zmq::buffer(recv_buf), zmq::recv_flags::none);
        if (debug_recv) {
            std::cout << cfg.path << " Received: ";
            for (size_t i = 0; i < Nchannels; i++) {
               std::cout << recv_buf[i] << " ";
            }
            std::cout << std::endl;
        }
        dq.push_back(recv_buf);
    }
    return 0;
}

#endif // CLIENTH
