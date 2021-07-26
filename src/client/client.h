/** @file */
#ifndef CLIENTH
#define CLIENTH

#include <iostream>
#include <array>

#include <boost/lockfree/spsc_queue.hpp>

#include "subscriber.h"
#include "data_config.h"
#include "queue_mgr.h"

/** 
 * @brief Receives data via tcp and pushes to processor queues.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * 
 * Client receives data accross tcp via Subscriber, and pushes data to its corresponding DataQueue to be processed by Processor. 
 */

template <size_t ConfigIndex>
class Client {
public:
    Client() = delete;
    Client(zmq::context_t &ctx);
    ~Client() = default;

    int run();
private:
    Subscriber<ConfigIndex> subscriber;
    QueueMgr<ConfigIndex>  q;

};

/** 
 * @brief Client constructor.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 */
template <size_t ConfigIndex>
inline Client<ConfigIndex>::Client(zmq::context_t &ctx) :
        subscriber {ctx}
        {}


/** 
 * @brief  Continuously receives data via Subscriber and pushes to DataQueue to be processed by Processor.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * @todo factor out recv functionality to subscriber class
 * @returns Runs indefinitely
 */
template <size_t ConfigIndex>
inline int Client<ConfigIndex>::run() {
    while(1) {
        std::array<double, ConfigList[ConfigIndex].Nchannels> recv_buf;
        auto res = this->subscriber.sub.recv(zmq::buffer(recv_buf), zmq::recv_flags::none);
        if (debug_recv) {
            std::cout << ConfigList[ConfigIndex].path << " Received: ";
            for (size_t i = 0; i < ConfigList[ConfigIndex].Nchannels; i++) {
               std::cout << recv_buf[i] << " ";
            }
            std::cout << std::endl;
        }
        q.push(recv_buf);
    }
    return 0;
}

#endif // CLIENTH
