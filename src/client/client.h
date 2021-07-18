#ifndef CLIENTH
#define CLIENTH

#include <iostream>
#include "subscriber.h"
#include "data_config.h"

template <size_t ConfigIndex>
class Client {

public:
    Client() = delete;
    Client(zmq::context_t &ctx);
    ~Client() = default;

    int run();
private:
    Subscriber subscriber;
};

template <size_t ConfigIndex>
Client<ConfigIndex>::Client(zmq::context_t &ctx) :
        subscriber {ctx, std::string(ConfigList[ConfigIndex].port)}
        {}

template <size_t ConfigIndex>
int Client<ConfigIndex>::run() {
    while(1) {
        std::array<double, ConfigList[ConfigIndex].Nchannels> buf;
        auto res = this->subscriber.sub.recv(zmq::buffer(buf), zmq::recv_flags::none);
    }
    return 0;
}

#endif // CLIENTH
