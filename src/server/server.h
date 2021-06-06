#ifndef SERVERH
#define SERVERH

#include "h5_data.h"
#include "publisher.h"
#include "config.h"

template <size_t Nchannels>
class Server {
public:
    Server() = delete;
    Server(Config cfg, zmq::context_t &ctx);
    ~Server() = default;
    int run();

private:
    Publisher publisher;
    H5Data<Nchannels> data;
    Config cfg;
};


template <size_t Nchannels>
Server<Nchannels>::Server(Config cfg, zmq::context_t &ctx) :
        cfg{cfg},
        publisher{ctx, std::string(cfg.port)},
        data {H5Data<Nchannels>("../data/S2.h5")}
    {}


template <size_t Nchannels>
int Server<Nchannels>::run() {
    int i = 0;
    std::cout << "Running " << this->cfg.path << std::endl;
    int dt_us = int(1e6/this->cfg.fs);
    const size_t nsteps = 1000;
    int expected_duration = nsteps * dt_us;
    double data_buf[nsteps][Nchannels];
    int status = this->data.read_chunk(std::string(cfg.path), 0, nsteps-1, data_buf);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < nsteps; i++) {
        auto res = this->publisher.send(data_buf[i][0]);
        std::this_thread::sleep_for(std::chrono::microseconds(dt_us));
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
    std::cout << this->cfg.path << " finished in " << us.count() << " us."  << std::endl;
    std::cout << this->cfg.path << " expected duration " << expected_duration << " us."  << std::endl;
    std::cout << ((float(us.count()) - expected_duration)/expected_duration) * 100 << " percent difference." << std::endl;
    return 0;
}

#endif // SERVERH
