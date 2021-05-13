#ifndef PUBLISHERH
#define PUBLISHERH

#include <string>

class Publisher {
public:
    Publisher() = delete;
    Publisher(zmq::context_t &ctx, const std::string tcp_port);
    ~Publisher() = default;
    zmq::socket_t pub;
};

#endif // PUBLISHERH
