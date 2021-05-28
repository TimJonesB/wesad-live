#include <string>
#include <zmq.hpp>
#include "publisher.h"

Publisher::Publisher(zmq::context_t &ctx, const std::string tcp_port): pub{ctx, ZMQ_PUB} {
    pub.bind(tcp_port);
}
