cmake_minimum_required(VERSION 3.0)

project(WesadLive VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(WesadLive demo.cpp)

add_subdirectory(src)

find_package(HDF5 REQUIRED COMPONENTS C)
find_package(Threads REQUIRED)

target_include_directories(WesadLive PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${HDF5_INCLUDE_DIRS}
                           src
                          )

target_link_libraries (WesadLive 
                       ${HDF5_C_LIBRARIES}
                       src
                       ${CMAKE_THREAD_LIBS_INIT}
                       )
