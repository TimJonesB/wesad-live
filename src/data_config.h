#ifndef DATACONFIGH
#define DATACONFIGH

#include <string_view>

struct Config {
    size_t index;
    std::string_view path;
    std::string_view port;
    int fs;
    size_t Nchannels;
    constexpr Config(const size_t index, const std::string_view path, const std::string_view port, const int fs, const size_t Nchannels ) :
                     index{index}, path {path}, port {port}, fs {fs}, Nchannels{Nchannels} {}
};


constexpr size_t nsteps = 10000;
constexpr int chest_fs = 700;
constexpr bool test_speed = 1;
constexpr bool debug_recv = 0;
constexpr int data_queue_sz = 1024;

//                                     |      PATH       |           PORT           |   fs   | nchan
//                               ==========================================================================

constexpr std::array ConfigList {Config  {0, "/signal/chest/ACC",  "tcp://127.0.0.1:5000", chest_fs, 3},
                                 Config  {1, "/signal/chest/ECG",  "tcp://127.0.0.1:5001", chest_fs, 1},
                                 Config  {2, "/signal/chest/EMG",  "tcp://127.0.0.1:5002", chest_fs, 1},
                                 Config  {3, "/signal/chest/EDA",  "tcp://127.0.0.1:5003", chest_fs, 1},
                                 Config  {4, "/signal/chest/Temp", "tcp://127.0.0.1:5004", chest_fs, 1}, // *32 bit int
                                 Config  {5, "/signal/chest/Resp", "tcp://127.0.0.1:5005", chest_fs, 1},
                                 Config  {6, "/signal/wrist/ACC",  "tcp://127.0.0.1:5006", 32,       3},
                                 Config  {7, "/signal/wrist/BVP",  "tcp://127.0.0.1:5007", 64,       1},
                                 Config  {8, "/signal/wrist/EDA",  "tcp://127.0.0.1:5008", 4,        1},
                                 Config  {9, "/signal/wrist/TEMP", "tcp://127.0.0.1:5009", 4,        1}};

#endif // DATACONFIGH
