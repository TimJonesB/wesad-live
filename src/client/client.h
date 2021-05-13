#ifndef CLIENTH
#define CLIENTH

#include "subscriber.h"
const std::string tcp_port{"tcp://127.0.0.1:5555"};

class Client {

public:
    Client() = delete;
    Client(zmq::context_t &ctx, const std::string tcp_port = tcp_port);
    ~Client() = default;

    int run();
private:
    Subscriber subscriber;
};


#endif // CLIENTH
