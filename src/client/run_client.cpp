#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "client.h"

int main() {
    zmq::context_t ctx;
    Client(ctx).run();
    return 0;
}
