#ifndef PUBLISHERH
#define PUBLISHERH

#include <string>

#include "zmq.hpp"

template <size_t Nchannels>
class Publisher {
public:
    Publisher() = delete;
    Publisher(zmq::context_t &ctx, const std::string tcp_port);
    ~Publisher() = default;
    template <typename T>
    zmq::recv_result_t send(const T data[]);

private:
    zmq::socket_t pub;
};


template <size_t Nchannels>
Publisher<Nchannels>::Publisher(zmq::context_t &ctx, const std::string tcp_port): pub{ctx, ZMQ_PUB} {
    pub.bind(tcp_port);
}

template <size_t Nchannels>
template <typename T>
zmq::recv_result_t Publisher<Nchannels>::send(const T data[]) {
    zmq::const_buffer buf{data, Nchannels};
    return this->pub.send(buf, zmq::send_flags::none);
}

#endif // PUBLISHERH