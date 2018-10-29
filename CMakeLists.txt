cmake_minimum_required (VERSION 3.8.1)

project(ivs)

add_definitions("-std=c++14")

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
find_package(opencv REQUIRED)

add_executable(abtsract_class_interface abtsract_class_interface.cpp)
target_link_libraries(abtsract_class_interface opencv::opencv)

add_executable(function_list_interface function_list_interface.cpp)
target_link_libraries(function_list_interface opencv::opencv)
