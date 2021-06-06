#ifndef H5SANDBOXH
#define H5SANDBOXH

#include <string_view>

struct Config {
    std::string_view path;
    std::string_view port;
    int fs;
    size_t Nchannels;
    constexpr Config(const std::string_view path, const std::string_view port, const int fs, const size_t Nchannels ) :
                     path {path}, port {port}, fs {fs}, Nchannels{Nchannels} {}
};

//                 NAME   |     PATH        |        PORT           |    fs | nchan
//              ================================================================

constexpr Config Chest_EMG{"/signal/chest/EMG", "tcp://127.0.0.1:5000", 100, 1};
constexpr Config Wrist_ACC{"/signal/wrist/ACC", "tcp://127.0.0.1:5001", 700, 3};

#endif // H5SANDBOXH