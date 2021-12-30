cmake_minimum_required(VERSION 3.0)
project(Cpp_Ecg_Detectors)

add_library(Cpp_Ecg_Detectors SHARED
            realtime/DetectorEngZeeRealTime.cpp
            realtime/DetectorPanTompkins.cpp
            iir1/Butterworth.cpp
            iir1/Biquad.cpp
            iir1/Cascade.cpp
            iir1/PoleFilter.cpp
            iir1/State.cpp
            handlers/MoveDifference.cpp
            handlers/Convolution.cpp
            handlers/MWA.cpp
            handlers/VectorFunctions.cpp
            handlers/PanPeakDetector.cpp
)
set(CMAKE_CXX_STANDARD 14)

target_include_directories(Cpp_Ecg_Detectors PUBLIC
                           handlers
                           iir1
                           realtime)
