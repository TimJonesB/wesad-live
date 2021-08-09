/** @file */
#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>

#include "server.h"
#include "data_config.h"

/** 
 * @brief TMP method to launch Server<0> through Server<size(ConfigList)-1>
 * @param v Vector of futures to save off to.
 * @param ctx ZMQ socket context.
 * @tparam CurrentIndex Index of the server being launched. 
 */
template <size_t CurrentIndex>
int launch_servers(std::vector<std::future<int>> &v, zmq::context_t &ctx) {
    if constexpr(CurrentIndex){
        v.push_back(std::async(std::launch::async, [&ctx](){return Server<CurrentIndex-1>(ctx).run();}));
        return launch_servers<CurrentIndex-1>(v, ctx);
    }
    else
        return 0;
}

/** 
 * @brief Entry point for the server application. 
 * @returns 0
 */
int main() {
    zmq::context_t ctx;
    std::vector<std::future<int>> v;
    launch_servers<std::size(ConfigList)>(v, ctx);
    return 0;
}
