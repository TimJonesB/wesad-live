/** @file */
#include <thread>
#include <chrono>
#include <future>

#include <zmq.hpp>

#include "client.h"
#include "data_config.h"
#include "processor.h"


/** 
 * @brief TMP method to launch Client<0> through Client<size(ConfigList)-1>
 * @param v Vector of futures to save off to.
 * @param ctx ZMQ socket context.
 * @tparam CurrentIndex Index of the client being launched. 
 * @returns 0
 */
template <size_t CurrentIndex>
int launch_clients(std::vector<std::future<int>> &v, zmq::context_t &ctx) {
    if constexpr(CurrentIndex){
        if constexpr(ConfigList[CurrentIndex-1].status == Cfg::ACTIVE) {
            v.push_back(std::async(std::launch::async, [&ctx](){return Client<CurrentIndex-1>(ctx).run();}));
        }
        return launch_clients<CurrentIndex-1>(v, ctx);
    }
    else {
        return 0;
    }
}


/** 
 * @brief Entry point for the client application. 
 * @returns 0
 */
int main() {
    zmq::context_t ctx;
    std::vector<std::future<int>> v;
    launch_clients<std::size(ConfigList)>(v, ctx);
    Processor p;
    p.run();
    return 0;
}
