#ifndef SUBSCRIBERH
#define SUBSCRIBERH

#include <string>

class Subscriber {
public:
    Subscriber() = delete;
    Subscriber(zmq::context_t &ctx, const std::string tcp_port);
    ~Subscriber() = default;
    zmq::socket_t sub;
};

#endif // SUBSCRIBERH
