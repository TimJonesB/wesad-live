add_executable(client
               run_client.cpp
               PanTompkinsQRS/panThompkins.cpp
               )

find_package(HDF5 REQUIRED COMPONENTS C)
find_package(cppzmq REQUIRED)
find_package(Boost REQUIRED)
find_package(Armadillo REQUIRED)
target_include_directories(client PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../panThompkinsQRS
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/..
                           ${PROJECT_BINARY_DIR}
                           ${HDF5_INCLUDE_DIRS}
                           ${Boost_INCLUDE_DIRS}
                           ${ARMADILLO_INCLUDE_DIRS}
                          )

target_link_libraries (client
                       ${HDF5_C_LIBRARIES}
                       cppzmq
                       ${Boost_LIBRARY_DIRS}
                       ${ARMADILLO_LIBRARIES}
                      )
