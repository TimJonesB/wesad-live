
add_library(server INTERFACE
           )
add_executable(server-bin
               run_server.cpp
               )
find_package(HDF5 REQUIRED COMPONENTS C)
find_package(cppzmq REQUIRED)

target_include_directories(server INTERFACE
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_CURRENT_SOURCE_DIR}/..
                            ${PROJECT_BINARY_DIR}
                            ${HDF5_INCLUDE_DIRS}
                          )

target_link_libraries (server INTERFACE
                       ${HDF5_C_LIBRARIES}
                       cppzmq
                      )

target_include_directories(server-bin PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_CURRENT_SOURCE_DIR}/..
                            ${PROJECT_BINARY_DIR}
                            ${HDF5_INCLUDE_DIRS}
                          )

target_link_libraries (server-bin
                       ${HDF5_C_LIBRARIES}
                       cppzmq
                      )
