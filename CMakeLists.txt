cmake_minimum_required(VERSION 3.0)

project(WesadLive VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(WesadLive 
               src/demo.cpp
            #    src/test_run.cpp
)

add_subdirectory(src/server)
add_subdirectory(src/client)


find_package(HDF5 REQUIRED COMPONENTS C)
find_package(Threads REQUIRED)
find_package(Armadillo REQUIRED)

target_include_directories(WesadLive PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${HDF5_INCLUDE_DIRS}
                           ${CMAKE_CURRENT_SOURCE_DIR}/src
                           ${CMAKE_CURRENT_SOURCE_DIR}/src/server
                           ${CMAKE_CURRENT_SOURCE_DIR}/src/client
                           ${CMAKE_CURRENT_SOURCE_DIR}/src/client/Cpp_Ecg_Detectors
                          )

target_link_libraries (WesadLive 
                       ${HDF5_C_LIBRARIES}
                       ${CMAKE_THREAD_LIBS_INIT}
                       server
                       client
                       )

# message(STATUS "PRINTING : ${HDF5_C_LIBRARIES}")
