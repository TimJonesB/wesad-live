#include <zmq.hpp>
#include <thread>
#include <chrono>
#include <future>

#include "client.h"
#include "data_config.h"


int main() {
    zmq::context_t ctx;
    std::future<int> f0 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_ACC.Nchannels>(ctx, Chest_ACC.port).run();});
    std::future<int> f1 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_ECG.Nchannels>(ctx, Chest_ECG.port).run();});
    std::future<int> f2 = std::async(std::launch::async,
                                     [&ctx](){return Client<Chest_EMG.Nchannels>(ctx, Chest_EMG.port).run();});
    return 0;
}
