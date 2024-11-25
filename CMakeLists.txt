cmake_minimum_required(VERSION 3.11)
project("Matrix")

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "-pedantic -Wextra -Wall")

add_subdirectory(src)
add_subdirectory(tests)