add_executable(server 
               run_server.cpp
               publisher.cpp
               )

find_package(HDF5 REQUIRED COMPONENTS C)
find_package(cppzmq REQUIRED)
target_include_directories(server PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_CURRENT_SOURCE_DIR}/..
                            ${PROJECT_BINARY_DIR}
                            ${HDF5_INCLUDE_DIRS}
                          )

target_link_libraries (server
                       ${HDF5_C_LIBRARIES}
                       cppzmq
                      )
