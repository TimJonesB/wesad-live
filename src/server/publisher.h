#ifndef PUBLISHERH
#define PUBLISHERH

#include <string>
#include <algorithm>

#include "zmq.hpp"

template <size_t Nchannels>
class Publisher {
public:
    Publisher() = delete;
    Publisher(zmq::context_t &ctx, const std::string tcp_port);
    ~Publisher() = default;
    template <typename T>
    zmq::recv_result_t send(const std::array<T,Nchannels> &arr);

private:
    zmq::socket_t pub;
};


template <size_t Nchannels>
Publisher<Nchannels>::Publisher(zmq::context_t &ctx, const std::string tcp_port): pub{ctx, ZMQ_PUB} {
    pub.bind(tcp_port);
}

template <size_t Nchannels>
template <typename T>
zmq::recv_result_t Publisher<Nchannels>::send(const std::array<T,Nchannels> &arr) {
    auto res =  this->pub.send(zmq::buffer(arr), zmq::send_flags::none);
    return res;
}

#endif // PUBLISHERH
