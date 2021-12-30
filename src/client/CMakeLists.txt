
add_library(client INTERFACE
            )

add_executable(client-bin
               run_client.cpp
               )

find_package(HDF5 REQUIRED COMPONENTS C)
find_package(cppzmq REQUIRED)
find_package(Boost REQUIRED)
find_package(Armadillo REQUIRED)

add_subdirectory(Cpp_Ecg_Detectors)

target_include_directories(client INTERFACE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/..
                           ${PROJECT_BINARY_DIR}
                           ${HDF5_INCLUDE_DIRS}
                           ${Boost_INCLUDE_DIRS}
                           ${ARMADILLO_INCLUDE_DIRS}
                           Cpp_Ecg_Detectors
                          )

target_link_libraries (client INTERFACE
                       ${HDF5_C_LIBRARIES}
                       cppzmq
                       ${Boost_LIBRARY_DIRS}
                       ${ARMADILLO_LIBRARIES}
                       Cpp_Ecg_Detectors
                      )

target_include_directories(client-bin PUBLIC 
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/..
                           ${PROJECT_BINARY_DIR}
                           ${HDF5_INCLUDE_DIRS}
                           ${Boost_INCLUDE_DIRS}
                           ${ARMADILLO_INCLUDE_DIRS}
                           Cpp_Ecg_Detectors
                          )

target_link_libraries (client-bin
                       ${HDF5_C_LIBRARIES}
                       cppzmq
                       ${Boost_LIBRARY_DIRS}
                       ${ARMADILLO_LIBRARIES}
                       Cpp_Ecg_Detectors
                      )