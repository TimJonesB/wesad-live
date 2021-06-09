
#include <iostream>
#include <future>
#include <thread>

#include "data_config.h"

int main() {
    std::future<int> f1 = std::async(std::launch::async,
                                     [](){return system("./src/server/server");});

    std::future<int> f2 = std::async(std::launch::async,
                                     [](){return system("./src/client/client");});


    return 0;
}
