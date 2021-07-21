/** @file */
#ifndef DATACONFIGH
#define DATACONFIGH

#include <string_view>

/** 
 * @brief  Holds configuration for a single data stream/data source.
 */
struct DataStreamConfig {
    std::string_view path; /// path from root of HDF5 data source file to data stream data
    std::string_view port; /// tcp port to send/read data from for data stream
    int fs; /// frequency to transmit data over (sampling frequency)
    size_t Nchannels; /// number of channels per data transmission (ie 3 for acceleration x,y,z, 1 for ECG signal)
    constexpr DataStreamConfig(const std::string_view path, const std::string_view port, const int fs, const size_t Nchannels ) :
                               path {path}, port {port}, fs {fs}, Nchannels{Nchannels} {}
};


constexpr size_t nsteps = 10000; /// N steps of data to send per channel for simulation; Also determines data chunk pre-read buffer size
constexpr int chest_fs = 700; /// Reference param for chest data sampling frequency
constexpr bool test_speed = 1; /// Triggers a data transmission speed test
constexpr bool debug_recv = 0; /// Debugs recv data in Server application
constexpr int data_queue_sz = 1024; /// Size of data queue

/** 
 * @brief  List of DataStreamConfigs.
 *                                                 |      PATH       |           PORT           |   fs   | Nchannels
 *                                          ==========================================================================
 */
constexpr std::array ConfigList {DataStreamConfig  {"/signal/chest/ACC",  "tcp://127.0.0.1:5000", chest_fs, 3},
                                 DataStreamConfig  {"/signal/chest/ECG",  "tcp://127.0.0.1:5001", chest_fs, 1},
                                 DataStreamConfig  {"/signal/chest/EMG",  "tcp://127.0.0.1:5002", chest_fs, 1},
                                 DataStreamConfig  {"/signal/chest/EDA",  "tcp://127.0.0.1:5003", chest_fs, 1},
                                 DataStreamConfig  {"/signal/chest/Temp", "tcp://127.0.0.1:5004", chest_fs, 1}, // *32 bit int
                                 DataStreamConfig  {"/signal/chest/Resp", "tcp://127.0.0.1:5005", chest_fs, 1},
                                 DataStreamConfig  {"/signal/wrist/ACC",  "tcp://127.0.0.1:5006", 32,       3},
                                 DataStreamConfig  {"/signal/wrist/BVP",  "tcp://127.0.0.1:5007", 64,       1},
                                 DataStreamConfig  {"/signal/wrist/EDA",  "tcp://127.0.0.1:5008", 4,        1},
                                 DataStreamConfig  {"/signal/wrist/TEMP", "tcp://127.0.0.1:5009", 4,        1}};

#endif // DATACONFIGH
