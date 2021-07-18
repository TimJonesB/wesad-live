#include <thread>
#include <chrono>
#include <future>

#include <zmq.hpp>

#include "client.h"
#include "data_config.h"
#include "processor.h"

int main() {
    zmq::context_t ctx;
    std::future<int> f0 = std::async(std::launch::async, [&ctx](){return Client<0>(ctx, q0).run();});
    std::future<int> f1 = std::async(std::launch::async, [&ctx](){return Client<1>(ctx, q1).run();});
    std::future<int> f2 = std::async(std::launch::async, [&ctx](){return Client<2>(ctx, q2).run();});
    std::future<int> f3 = std::async(std::launch::async, [&ctx](){return Client<3>(ctx, q3).run();});
    // std::future<int> f4 = std::async(std::launch::async, [&ctx](){return Client<4>(ctx, q4).run();});
    std::future<int> f5 = std::async(std::launch::async, [&ctx](){return Client<5>(ctx, q5).run();});
    std::future<int> f6 = std::async(std::launch::async, [&ctx](){return Client<6>(ctx, q6).run();});
    std::future<int> f7 = std::async(std::launch::async, [&ctx](){return Client<7>(ctx, q7).run();});
    std::future<int> f8 = std::async(std::launch::async, [&ctx](){return Client<8>(ctx, q8).run();});
    std::future<int> f9 = std::async(std::launch::async, [&ctx](){return Client<9>(ctx, q9).run();});
    
    Processor p;
    p.run();
    return 0;
}
