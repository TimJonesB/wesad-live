#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <future>

#include "server.h"
#include "data_config.h"

template <size_t index>
void launch_servers(std::vector<std::future<int>> &v, zmq::context_t &ctx) {
    if constexpr(index-1){
        v.push_back(std::async(std::launch::async, [&ctx](){return Server<index-1>(ctx).run();}));
        launch_servers<index-1>(v, ctx);
    }
    else
        return;
}

int main() {
    zmq::context_t ctx;
    std::vector<std::future<int>> v;
    launch_servers<std::size(ConfigList)>(v, ctx);
    return 0;
}
