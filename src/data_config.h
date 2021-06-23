#ifndef DATACONFIGH
#define DATACONFIGH

#include <string_view>

struct Config {
    std::string_view path;
    std::string_view port;
    int fs;
    size_t Nchannels;
    constexpr Config(const std::string_view path, const std::string_view port, const int fs, const size_t Nchannels ) :
                     path {path}, port {port}, fs {fs}, Nchannels{Nchannels} {}
};

constexpr size_t nsteps = 10000;
constexpr int chest_fs = 700;
constexpr bool test_speed = 1;
constexpr bool debug_recv = 1;
constexpr int data_queue_sz = 1024;

//                   NAME   |      PATH       |           PORT           |   fs   | nchan
//               ==========================================================================
constexpr Config Chest_ACC  {"/signal/chest/ACC",  "tcp://127.0.0.1:5000", chest_fs, 3};
constexpr Config Chest_ECG  {"/signal/chest/ECG",  "tcp://127.0.0.1:5001", chest_fs, 1};
constexpr Config Chest_EMG  {"/signal/chest/EMG",  "tcp://127.0.0.1:5002", chest_fs, 1};
constexpr Config Chest_EDA  {"/signal/chest/EDA",  "tcp://127.0.0.1:5003", chest_fs, 1};
// constexpr Config Chest_TEMP {"/signal/chest/Temp", "tcp://127.0.0.1:5004", chest_fs, 1}; // *32 bit int
constexpr Config Chest_RESP {"/signal/chest/Resp", "tcp://127.0.0.1:5005", chest_fs, 1};
constexpr Config Wrist_ACC  {"/signal/wrist/ACC",  "tcp://127.0.0.1:5006", 32,       3};
constexpr Config Wrist_BVP  {"/signal/wrist/BVP",  "tcp://127.0.0.1:5007", 64,       1};
constexpr Config Wrist_EDA  {"/signal/wrist/EDA",  "tcp://127.0.0.1:5008", 4,        1};
constexpr Config Wrist_TEMP {"/signal/wrist/TEMP", "tcp://127.0.0.1:5009", 4,        1};

#endif // DATACONFIGH
