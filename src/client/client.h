#ifndef CLIENTH
#define CLIENTH

#include "subscriber.h"

class Client {

public:
    Client() = delete;
    Client(zmq::context_t &ctx, const std::string tcp_port);
    ~Client() = default;

    int run();
private:
    Subscriber subscriber;
};


#endif // CLIENTH
