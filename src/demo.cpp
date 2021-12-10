/** @file */
/** 
 * @mainpage WESAD-LIVE Library Documentation
 * @section intro_sec Introduction
 * This is the wesad-live documentation.
 * Deps: See wesad-live README
 */ 
#include <iostream>
#include <future>
#include <thread>
/** 
 * @brief Entry point for demonstration application. 
 * Launches the client and server applications.
 */
int main() {
    std::future<int> f1 = std::async(std::launch::async,
                                     [](){return system("./src/server/server");});

    std::future<int> f2 = std::async(std::launch::async,
                                     [](){return system("./src/client/client");});

    return 0;
}
