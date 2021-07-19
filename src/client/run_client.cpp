#include <thread>
#include <chrono>
#include <future>

#include <zmq.hpp>

#include "client.h"
#include "data_config.h"
#include "processor.h"

int main() {


    zmq::context_t ctx;
    std::future<int> f0 = std::async(std::launch::async, [&ctx](){return Client<0>(ctx).run();});
    std::future<int> f1 = std::async(std::launch::async, [&ctx](){return Client<1>(ctx).run();});
    std::future<int> f2 = std::async(std::launch::async, [&ctx](){return Client<2>(ctx).run();});
    std::future<int> f3 = std::async(std::launch::async, [&ctx](){return Client<3>(ctx).run();});
    // std::future<int> f4 = std::async(std::launch::async, [&ctx](){return Client<4>( q4).run();});
    std::future<int> f5 = std::async(std::launch::async, [&ctx](){return Client<5>(ctx).run();});
    std::future<int> f6 = std::async(std::launch::async, [&ctx](){return Client<6>(ctx).run();});
    std::future<int> f7 = std::async(std::launch::async, [&ctx](){return Client<7>(ctx).run();});
    std::future<int> f8 = std::async(std::launch::async, [&ctx](){return Client<8>(ctx).run();});
    std::future<int> f9 = std::async(std::launch::async, [&ctx](){return Client<9>(ctx).run();});
    
    Processor p;
    p.run();
    return 0;
}
