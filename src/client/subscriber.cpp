#include <string>
#include <zmq.hpp>

#include "subscriber.h"

Subscriber::Subscriber(zmq::context_t &ctx, const std::string tcp_port): sub{ctx, ZMQ_SUB} {
    sub.connect(tcp_port);
    sub.setsockopt(ZMQ_SUBSCRIBE, "", 0); // need to est. initial msg filter, because everything is filtered by default...
}
