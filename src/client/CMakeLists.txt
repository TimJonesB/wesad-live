add_executable(client
               client.cpp
               subscriber.cpp
               run_client.cpp)

find_package(HDF5 REQUIRED COMPONENTS C)
find_package(cppzmq REQUIRED)
target_include_directories(client PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${PROJECT_BINARY_DIR}
                            ${HDF5_INCLUDE_DIRS}
                          )

target_link_libraries (client
                       ${HDF5_C_LIBRARIES}
                       cppzmq
                      )
