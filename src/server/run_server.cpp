#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "H5Cpp.h"
#include "server.h"
#include "h5_data.h"

int main() {
    zmq::context_t ctx;
    Server(ctx).run();
    return 0;
}
