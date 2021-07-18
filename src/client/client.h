#ifndef CLIENTH
#define CLIENTH

#include <iostream>
#include <array>

#include <boost/lockfree/spsc_queue.hpp>

#include "subscriber.h"
#include "data_config.h"

// TODO: better way than global?
boost::lockfree::spsc_queue<std::array<double, ConfigList[0].Nchannels>> q0 {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, ConfigList[1].Nchannels>> q1 {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, ConfigList[2].Nchannels>> q2 {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, ConfigList[3].Nchannels>> q3 {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, ConfigList[4].Nchannels>> q4 {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, ConfigList[5].Nchannels>> q5 {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, ConfigList[6].Nchannels>> q6 {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, ConfigList[7].Nchannels>> q7 {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, ConfigList[8].Nchannels>> q8 {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, ConfigList[9].Nchannels>> q9 {data_queue_sz};

template <size_t ConfigIndex>
class Client {
public:
    Client() = delete;
    Client(zmq::context_t &ctx, boost::lockfree::spsc_queue<std::array<double, ConfigList[ConfigIndex].Nchannels>> &q);
    ~Client() = default;

    int run();
private:
    Subscriber subscriber;
    std::unique_ptr<boost::lockfree::spsc_queue<std::array<double, ConfigList[ConfigIndex].Nchannels>>>  q;

};

template <size_t ConfigIndex>
Client<ConfigIndex>::Client(zmq::context_t &ctx, boost::lockfree::spsc_queue<std::array<double, ConfigList[ConfigIndex].Nchannels>> &q) :
        subscriber {ctx, std::string(ConfigList[ConfigIndex].port)},
        q{&q}
        {}

template <size_t ConfigIndex>
int Client<ConfigIndex>::run() {
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
        q->push(recv_buf);
    }
    return 0;
}

#endif // CLIENTH
