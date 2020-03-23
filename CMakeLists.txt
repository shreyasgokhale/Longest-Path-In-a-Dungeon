cmake_minimum_required(VERSION 3.10)
project(longest_path_cpp)

set(CMAKE_CXX_STANDARD 11)

add_executable(longest_path_cpp main.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/map.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)