#ifndef SERVERH
#define SERVERH

#include "h5_data.h"
#include "publisher.h"


class Server {

public:
    Server() = delete;
    Server(zmq::context_t &ctx, const std::string tcp_port);
    ~Server() = default;

    int run();
private:
    Publisher publisher;
    H5Data data;
};



#endif // SERVERH
