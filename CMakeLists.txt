cmake_minimum_required(VERSION 3.11)
project("Matrix")

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_library(matrix INTERFACE)

target_include_directories(matrix INTERFACE ./inc)

add_subdirectory(src)
add_subdirectory(tests)