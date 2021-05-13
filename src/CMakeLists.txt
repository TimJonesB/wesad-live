add_library(src h5_sandbox.cpp)


add_subdirectory(server)
add_subdirectory(client)


find_package(HDF5 REQUIRED COMPONENTS C CXX)
target_include_directories(src PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${PROJECT_BINARY_DIR}
                            ${HDF5_INCLUDE_DIRS}
                          )

target_link_libraries (src 
                       ${HDF5_CXX_LIBRARIES}
                      )


# add_custom_target(run_them_together_easily
#     COMMAND $<TARGET_FILE:server>
#     COMMAND $<TARGET_FILE:client>
# )
