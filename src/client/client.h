#ifndef CLIENTH
#define CLIENTH

#include "subscriber.h"

template <size_t Nchannels>
class Client {

public:
    Client() = delete;
    Client(zmq::context_t &ctx, const std::string_view tcp_port);
    ~Client() = default;

    int run();
private:
    Subscriber subscriber;
};

template <size_t Nchannels>
Client<Nchannels>::Client(zmq::context_t &ctx, const std::string_view tcp_port): subscriber {ctx, std::string(tcp_port)} {}

template <size_t Nchannels>
int Client<Nchannels>::run() {
    while(1) {
        std::array<double, Nchannels> buf;
        auto res = this->subscriber.sub.recv(zmq::buffer(buf), zmq::recv_flags::none);
    }
    return 0;
}

#endif // CLIENTH
