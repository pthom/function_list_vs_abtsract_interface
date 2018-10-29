cmake_minimum_required (VERSION 3.8.1)

project(ivs)

add_definitions("-std=c++14")

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
find_package(opencv REQUIRED)

add_executable(with_interface with_interface.cpp)
target_link_libraries(with_interface opencv::opencv)

add_executable(with_struct with_struct.cpp)
target_link_libraries(with_struct opencv::opencv)
