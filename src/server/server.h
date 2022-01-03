/** @file */
#ifndef SERVERH
#define SERVERH

#include "h5_data.h"
#include "publisher.h"
#include "data_config.h"

/** 
 * @brief Reads data from HDF5 file and send to TCP port via ZMQ connection.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * @todo Factor out and clean up data transmission timing tests in run method
 * 
 * Server reads a large buffer of data from HDF5 file up front, and transmitts data at a rate according to ConfigList[ConfigIndex].fs . 
 */
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


/** 
 * @brief Server constructor.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 */
template <size_t ConfigIndex>
inline Server<ConfigIndex>::Server(zmq::context_t &ctx) :
        publisher{ctx},
        data {"../data/S2.h5"}
    {}

/** 
 * @brief  Continuously reads data from HDF5 file and sends data via Publisher.
 * @tparam ConfigIndex Index of the data stream in ConfigList.
 * @returns Runs indefinitely.
 */
template <size_t ConfigIndex>
inline int Server<ConfigIndex>::run() {

    // std::cout << "Running " << ConfigList[ConfigIndex].path << std::endl;
    int dt_us = int(1e6/ConfigList[ConfigIndex].fs);
    double data_buf[nsteps][ConfigList[ConfigIndex].Nchannels];
    int status = this->data.read_chunk(std::string(ConfigList[ConfigIndex].path), 0, nsteps-1, data_buf);
    int expected_duration = nsteps * dt_us;
    auto start = std::chrono::high_resolution_clock::now();
    std::array<double, ConfigList[ConfigIndex].Nchannels> arr;
    for (size_t i = 0; i < nsteps; i++) {
        std::copy(std::begin(data_buf[i]), std::end(data_buf[i]), arr.begin());
        auto res = this->publisher.send(arr);
        std::this_thread::sleep_for(std::chrono::microseconds(dt_us));
    }
    if (test_speed) {
        auto finish = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
        std::cout << ConfigList[ConfigIndex].path << " finished in " << us.count() << " us."  << std::endl;
        std::cout << ConfigList[ConfigIndex].path << " expected duration " << expected_duration << " us."  << std::endl;
        std::cout << ((float(us.count()) - expected_duration)/expected_duration) * 100 << " percent difference." << std::endl;
    }
    return 0;
}

#endif // SERVERH
