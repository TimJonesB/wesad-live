#ifndef H5SANDBOXH
#define H5SANDBOXH

#include <map>
#include <string>

#define xxxx 4


namespace Config {
    const std::map<std::string, int> fs {{"/signal/chest/EMG", 100},
                                         {"/signal/wrist/EDA", 200},
                                         {"/signal/wrist/ACC", 300}};

    const std::map<std::string, std::string> ports {{"/signal/chest/EMG", "tcp://127.0.0.1:5000"},
                                                    {"/signal/wrist/EDA", "tcp://127.0.0.1:5001"},
                                                    {"/signal/wrist/ACC", "tcp://127.0.0.1:5002"}};
}

int run_it();

#endif // H5SANDBOXH