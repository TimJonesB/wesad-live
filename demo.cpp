
#include <iostream>
#include "h5_sandbox.h"
#include <future>
#include <thread>

int main() {
    std::future<int> f1 = std::async(std::launch::async,
                                     [](){return system("./src/server/server");});

    std::future<int> f2 = std::async(std::launch::async,
                                     [](){return system("./src/client/client");});


    return 0;
}
