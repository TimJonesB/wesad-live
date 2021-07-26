/** @file */
#ifndef PUBLISHERH
#define PUBLISHERH

#include <string>
#include <algorithm>

#include "zmq.hpp"
#include "data_config.h"
 
/** 
 * @brief Owns the zmq socket PUB connection to tcp port.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 */
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


/** 
 * @brief Connects to tcp port and sets publisher option.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * @param ctx ZMQ context.
 */
template <size_t ConfigIndex>
inline Publisher<ConfigIndex>::Publisher(zmq::context_t &ctx): pub{ctx, ZMQ_PUB} {
    pub.bind(std::string{ConfigList[ConfigIndex].port});
}

/** 
 * @brief Sends std::array to client over ZMQ tcp socket connection
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * @tparam T type of arr members
 * @param arr Array of data to send over publisher connection.
 * @returns number of bytes if successful
 */
template <size_t ConfigIndex>
template <typename T>
inline zmq::recv_result_t Publisher<ConfigIndex>::send(const std::array<T, ConfigList[ConfigIndex].Nchannels> &arr) {
    auto res =  this->pub.send(zmq::buffer(arr), zmq::send_flags::none);
    return res;
}

#endif // PUBLISHERH
