#ifndef SERVERH
#define SERVERH

#include "h5_data.h"
#include "publisher.h"

const std::string tcp_port{"tcp://127.0.0.1:5555"};

class Server {

public:
    Server() = delete;
    Server(zmq::context_t &ctx, const std::string tcp_port = tcp_port);
    ~Server() = default;

    int run();
private:
    Publisher publisher;
    H5Data data;
};



#endif // SERVERH
