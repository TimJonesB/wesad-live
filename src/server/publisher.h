#ifndef PUBLISHERH
#define PUBLISHERH

#include <string>

class Publisher {
public:
    Publisher() = delete;
    Publisher(zmq::context_t &ctx, const std::string tcp_port);
    ~Publisher() = default;
    template <typename T>
    zmq::recv_result_t send(const T &data);

private:
    zmq::socket_t pub;
};


template <typename T>
zmq::recv_result_t Publisher::send(const T &data) {
    zmq::message_t msg{std::to_string(data)};
    return this->pub.send(msg, zmq::send_flags::none);
}

#endif // PUBLISHERH