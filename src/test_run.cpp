
/** @file */
/** 
 * @mainpage WESAD-LIVE Library Documentation
 * @section intro_sec Introduction
 * This is the wesad-live documentation.
 * Deps: See wesad-live README
 */ 
#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include "h5_data.h"
#include "data_config.h"
#include "processor.h"
#include <boost/circular_buffer.hpp>
/** 
 * @brief Entry point for demonstration application. 
 * Launches the client and server applications.
 */
int main() {
    constexpr size_t channel = 8;
    auto hd = H5Data<channel> {"../data/S2.h5"};
    const size_t bufsz = 7000;
    double buf[bufsz][1];
    hd.read_chunk("/signal/wrist/TEMP", 2000, 2000+bufsz, buf);
    std::vector<double> v;
    std::array<double, NumberOfFeatures> state;
    std::array<double, 1> arr;
    FeatureProcessor<channel> p;
    for (int i = 0; i < bufsz; i++) {
    // for (int i = 0; i < 100; i++) {
        std::copy(std::begin(buf[i]), std::end(buf[i]), arr.begin());
        p.process(arr, state);
        // std::cout << "state 3: " << state[2] << std::endl;
        print_state(state);
    }
    
    return 0;
}
