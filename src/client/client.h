#ifndef CLIENTH
#define CLIENTH

#include <iostream>
#include <array>

#include <boost/lockfree/spsc_queue.hpp>

#include "subscriber.h"
#include "data_config.h"
#include "queue_mgr.h"

template <size_t ConfigIndex>
class Client {
public:
    Client() = delete;
    Client(zmq::context_t &ctx);
    ~Client() = default;

    int run();
private:
    Subscriber subscriber;
    QueueMgr<ConfigIndex>  q;

};


template <size_t ConfigIndex>
inline Client<ConfigIndex>::Client(zmq::context_t &ctx) :
        subscriber {ctx, std::string(ConfigList[ConfigIndex].port)}
        {}


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
