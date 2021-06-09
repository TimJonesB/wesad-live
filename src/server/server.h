#ifndef SERVERH
#define SERVERH

#include "h5_data.h"
#include "publisher.h"
#include "data_config.h"

template <size_t Nchannels>
class Server {
public:
    Server() = delete;
    Server( zmq::context_t &ctx, Config cfg);
    ~Server() = default;
    int run();

private:
    Publisher<Nchannels> publisher;
    H5Data<Nchannels> data;
    Config cfg;
};


template <size_t Nchannels>
Server<Nchannels>::Server(zmq::context_t &ctx, Config cfg) :
        publisher{ctx, std::string(cfg.port)},
        cfg{cfg},
        data {"../data/S2.h5"}
    {}

template <size_t Nchannels>
int Server<Nchannels>::run() {
    std::cout << "Running " << this->cfg.path << std::endl;
    int dt_us = int(1e6/this->cfg.fs);
    double data_buf[nsteps][Nchannels];
    int status = this->data.read_chunk(std::string(cfg.path), 0, nsteps-1, data_buf);
    int expected_duration = nsteps * dt_us;
    auto start = std::chrono::high_resolution_clock::now();
    std::array<double, Nchannels> arr;
    for (size_t i = 0; i < nsteps; i++) {
        auto res = this->publisher.send(arr);
        std::this_thread::sleep_for(std::chrono::microseconds(dt_us));
    }
    if (test_speed) {
        auto finish = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
        std::cout << this->cfg.path << " finished in " << us.count() << " us."  << std::endl;
        std::cout << this->cfg.path << " expected duration " << expected_duration << " us."  << std::endl;
        std::cout << ((float(us.count()) - expected_duration)/expected_duration) * 100 << " percent difference." << std::endl;
    }
    return 0;
}

#endif // SERVERH
