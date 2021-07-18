#ifndef SERVERH
#define SERVERH

#include "h5_data.h"
#include "publisher.h"
#include "data_config.h"

template <size_t ConfigIndex>
class Server {
public:
    Server() = delete;
    Server(zmq::context_t &ctx);
    ~Server() = default;
    int run();

private:
    Publisher<ConfigIndex> publisher;
    H5Data<ConfigIndex> data;
};


template <size_t ConfigIndex>
Server<ConfigIndex>::Server(zmq::context_t &ctx) :
        publisher{ctx},
        data {"../data/S2.h5"}
    {}

template <size_t ConfigIndex>
int Server<ConfigIndex>::run() {

    constexpr size_t Nchannels = ConfigList[ConfigIndex].Nchannels;
    constexpr Config cfg = ConfigList[ConfigIndex];

    std::cout << "Running " << cfg.path << std::endl;
    int dt_us = int(1e6/cfg.fs);
    double data_buf[nsteps][Nchannels];
    int status = this->data.read_chunk(std::string(cfg.path), 0, nsteps-1, data_buf);
    int expected_duration = nsteps * dt_us;
    auto start = std::chrono::high_resolution_clock::now();
    std::array<double, Nchannels> arr;
    for (size_t i = 0; i < nsteps; i++) {
        std::copy(std::begin(data_buf[i]), std::end(data_buf[i]), arr.begin());
        auto res = this->publisher.send(arr);
        std::this_thread::sleep_for(std::chrono::microseconds(dt_us));
    }
    if (test_speed) {
        auto finish = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
        std::cout << cfg.path << " finished in " << us.count() << " us."  << std::endl;
        std::cout << cfg.path << " expected duration " << expected_duration << " us."  << std::endl;
        std::cout << ((float(us.count()) - expected_duration)/expected_duration) * 100 << " percent difference." << std::endl;
    }
    return 0;
}

#endif // SERVERH
