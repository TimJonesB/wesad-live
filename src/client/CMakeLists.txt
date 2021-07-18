FILE(GLOB alglib ${CMAKE_CURRENT_SOURCE_DIR}/../../alglib_3_17_0_cpp/src/*.cpp)
add_executable(client
               subscriber.cpp
               run_client.cpp
               ${alglib}
               )

find_package(HDF5 REQUIRED COMPONENTS C)
find_package(cppzmq REQUIRED)
find_package(Boost REQUIRED)
target_include_directories(client PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_CURRENT_SOURCE_DIR}/..
                            ${CMAKE_CURRENT_SOURCE_DIR}/../../alglib_3_17_0_cpp/src
                            ${PROJECT_BINARY_DIR}
                            ${HDF5_INCLUDE_DIRS}
                            ${Boost_INCLUDE_DIRS}
                          )

target_link_libraries (client
                       ${HDF5_C_LIBRARIES}
                       cppzmq
                       ${Boost_LIBRARY_DIRS}
                      )
