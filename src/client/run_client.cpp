#include <thread>
#include <chrono>
#include <future>

#include <zmq.hpp>

#include "client.h"
#include "data_config.h"
#include "processor.h"


template <size_t index>
void launch_clients(std::vector<std::future<int>> &v, zmq::context_t &ctx) {
    if constexpr(index-1){
        v.push_back(std::async(std::launch::async, [&ctx](){return Client<index-1>(ctx).run();}));
        launch_clients<index-1>(v, ctx);
    }
    else
        return;
}


int main() {
    zmq::context_t ctx;
    std::vector<std::future<int>> v;
    launch_clients<std::size(ConfigList)>(v, ctx);
    Processor p;
    p.run();
    return 0;
}
