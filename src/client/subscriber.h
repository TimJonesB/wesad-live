/** @file */
#ifndef SUBSCRIBERH
#define SUBSCRIBERH

#include <string>
#include <zmq.hpp>
#include "data_config.h"

/** 
 * @brief Owns the zmq socket SUB connection to tcp port
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 */
template <size_t ConfigIndex>
class Subscriber {
public:
    Subscriber() = delete;
    Subscriber(zmq::context_t &ctx);
    ~Subscriber() = default;
    zmq::socket_t sub;
};

/** 
 * @brief Connects to tcp port and sets subscription option.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * @param ctx ZMQ context.
 */
template <size_t ConfigIndex>
inline Subscriber<ConfigIndex>::Subscriber(zmq::context_t &ctx): sub{ctx, ZMQ_SUB} {
    sub.connect(std::string(ConfigList[ConfigIndex].port));
    sub.set(zmq::sockopt::subscribe, "");
}
#endif // SUBSCRIBERH
