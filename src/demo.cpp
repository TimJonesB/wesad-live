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
#include "realtime/Detectors.h"
/** 
 * @brief Entry point for demonstration application. 
 * Launches the client and server applications.
 */
int main() {
    // std::future<int> f1 = std::async(std::launch::async,
    //                                  [](){return system("./src/server/server");});

    // std::future<int> f2 = std::async(std::launch::async,
    //                                  [](){return system("./src/cl
    auto hd = H5Data<1> {"../data/S2.h5"};
    const size_t bufsz = 7000;
    double buf[bufsz][1];
    hd.read_chunk("/signal/chest/ECG", 2000, 2000+bufsz, buf);
    std::vector<double> v;
    for (int i = 0; i < bufsz; i++) {
        v.push_back(buf[i][0]);
    }
    int fs = 700;
    DetectorPanTompkins det = DetectorPanTompkins(fs);
    for (auto val : v) {
        auto res = det.processSample(val); 
        if (res != -1) {
            std::cout << "ding" << std::endl;
        }
    }

    return 0;
}



    // double fs = 512.0; // sampling frequency
    // DetectorEngZeeRealTime detector = DetectorEngZeeRealTime(fs); // create specific detector with inputs
    // double samples[] = {0}; // ECG signal - just for demonstration
    // // to simulate real-time procedure, we will use for
    // for (double sample: samples) {
    //     int qrs = detector.processSample(sample);
    //     if(qrs != -1){
    //         // -1 - nothing
    //         // otherwise - it is index of the QRS complex in signal
    //         // does not need to be in order for some detectors (sorting required in some cases)
    //     }
    // }
    // detector.reset(); // if something went wrong - this will empty memory in detector
    // // for new configuration create new detector object

