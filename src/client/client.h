#ifndef CLIENTH
#define CLIENTH

#include <iostream>
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
};

template <size_t Nchannels>
Client<Nchannels>::Client(zmq::context_t &ctx, Config cfg) :
        subscriber {ctx, std::string(cfg.port)},
        cfg{cfg} {}

template <size_t Nchannels>
int Client<Nchannels>::run() {
    while(1) {
        std::array<double, Nchannels> buf;
        auto res = this->subscriber.sub.recv(zmq::buffer(buf), zmq::recv_flags::none);
    }
    return 0;
}

#endif // CLIENTH
