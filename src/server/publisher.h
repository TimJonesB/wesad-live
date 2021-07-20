#ifndef PUBLISHERH
#define PUBLISHERH

#include <string>
#include <algorithm>

#include "zmq.hpp"
#include "data_config.h"

template <size_t ConfigIndex>
class Publisher {
public:
    Publisher() = delete;
    Publisher(zmq::context_t &ctx);
    ~Publisher() = default;
    template <typename T>
    zmq::recv_result_t send(const std::array<T, ConfigList[ConfigIndex].Nchannels> &arr);

private:
    zmq::socket_t pub;
};


template <size_t ConfigIndex>
inline Publisher<ConfigIndex>::Publisher(zmq::context_t &ctx): pub{ctx, ZMQ_PUB} {
    pub.bind(std::string{ConfigList[ConfigIndex].port});
}

template <size_t ConfigIndex>
template <typename T>
inline zmq::recv_result_t Publisher<ConfigIndex>::send(const std::array<T, ConfigList[ConfigIndex].Nchannels> &arr) {
    auto res =  this->pub.send(zmq::buffer(arr), zmq::send_flags::none);
    return res;
}

#endif // PUBLISHERH
