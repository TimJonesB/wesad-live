/** @file */
#ifndef DATACONFIGH
#define DATACONFIGH

#include <string_view>

/**
 * @brief  On/Off for each item in ConfigList
 */
enum class Cfg {
    DISABLED = 0,
    ACTIVE = 1
};

/** 
 * @brief  Holds configuration for a single data stream/data source.
 */
struct DataStreamConfig {
    std::string_view path; /// path from root of HDF5 data source file to data stream data
    std::string_view port; /// tcp port to send/read data from for data stream
    size_t fs; /// frequency to transmit data over (sampling frequency)
    size_t Nchannels; /// number of channels per data transmission (ie 3 for acceleration x,y,z, 1 for ECG signal)
    Cfg status; // stream on (Cfg::ACTIVE) or off(Cfg::DISABLED)
    constexpr DataStreamConfig(const std::string_view path, const std::string_view port, const size_t fs, const size_t Nchannels, Cfg status) :
                               path {path}, port {port}, fs {fs}, Nchannels{Nchannels}, status{status} {}
};


constexpr size_t nsteps = 10000; /// N steps of data to send per channel for simulation; Also determines data chunk pre-read buffer size
constexpr size_t chest_fs = 700; /// Reference param for chest data sampling frequency
constexpr size_t data_queue_sz = 1024; /// Size of data queue
constexpr bool test_speed = 0; /// Triggers a data transmission speed test
constexpr bool debug_recv = 0; /// Debugs recv data in Server application

constexpr size_t ProcBufLen = 6;
/** 
 * @brief  List of DataStreamConfigs.
 *                                                 |      PATH       |           PORT           |   fs   | Nchannels | On/off |
 *                                          =====================================================================================
 */
constexpr std::array ConfigList {DataStreamConfig  {"/signal/chest/ACC",  "tcp://127.0.0.1:5000", chest_fs, 3,       Cfg::ACTIVE},
                                 DataStreamConfig  {"/signal/chest/ECG",  "tcp://127.0.0.1:5001", chest_fs, 1,       Cfg::ACTIVE},
                                 DataStreamConfig  {"/signal/chest/EMG",  "tcp://127.0.0.1:5002", chest_fs, 1,       Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/chest/EDA",  "tcp://127.0.0.1:5003", chest_fs, 1,       Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/chest/Temp", "tcp://127.0.0.1:5004", chest_fs, 1,       Cfg::DISABLED}, // *32 bit int
                                 DataStreamConfig  {"/signal/chest/Resp", "tcp://127.0.0.1:5005", chest_fs, 1,       Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/wrist/ACC",  "tcp://127.0.0.1:5006", 32,       3,       Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/wrist/BVP",  "tcp://127.0.0.1:5007", 64,       1,       Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/wrist/EDA",  "tcp://127.0.0.1:5008", 4,        1,       Cfg::DISABLED},
                                 DataStreamConfig  {"/signal/wrist/TEMP", "tcp://127.0.0.1:5009", 4,        1,       Cfg::DISABLED}};

#endif // DATACONFIGH
