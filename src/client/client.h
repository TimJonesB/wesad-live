#ifndef CLIENTH
#define CLIENTH

#include <iostream>
#include <array>
#include <deque>
#include <boost/lockfree/spsc_queue.hpp>
#include "subscriber.h"
#include "data_config.h"

// TODO: better way than global?
boost::lockfree::spsc_queue<std::array<double, Chest_ACC.Nchannels>> Chest_ACC_q {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, Chest_ECG.Nchannels>> Chest_ECG_q {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, Chest_EMG.Nchannels>> Chest_EMG_q {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, Chest_EDA.Nchannels>> Chest_EDA_q {data_queue_sz};
// boost::lockfrespsc_e::queue<std::array<double, Chest_TEMP.Nchannels>> Chest_TEMP_q {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, Chest_RESP.Nchannels>> Chest_RESP_q {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, Wrist_ACC.Nchannels>> Wrist_ACC_q {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, Wrist_BVP.Nchannels>> Wrist_BVP_q {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, Wrist_EDA.Nchannels>> Wrist_EDA_q {data_queue_sz};
boost::lockfree::spsc_queue<std::array<double, Wrist_TEMP.Nchannels>> Wrist_TEMP_q {data_queue_sz};

template <size_t Nchannels>
class Client {

public:
    Client() = delete;
    Client(zmq::context_t &ctx, Config cfg, boost::lockfree::spsc_queue<std::array<double, Nchannels>> &q);
    ~Client() = default;

    int run();
private:
    Subscriber subscriber;
    Config cfg;
    std::unique_ptr<boost::lockfree::spsc_queue<std::array<double, Nchannels>>>  q;
};

template <size_t Nchannels>
Client<Nchannels>::Client(zmq::context_t &ctx, Config cfg, boost::lockfree::spsc_queue<std::array<double, Nchannels>> &q ) :
        subscriber {ctx, std::string(cfg.port)},
        cfg{cfg},
        q{&q} {}

template <size_t Nchannels>
int Client<Nchannels>::run() {
    while(1) {
        std::array<double, Nchannels> recv_buf;
        auto res = this->subscriber.sub.recv(zmq::buffer(recv_buf), zmq::recv_flags::none);
        if (debug_recv) {
            std::cout << cfg.path << " Received: ";
            for (size_t i = 0; i < Nchannels; i++) {
               std::cout << recv_buf[i] << " ";
            }
            std::cout << std::endl;
        }
        q->push(recv_buf);
    }
    return 0;
}

#endif // CLIENTH
