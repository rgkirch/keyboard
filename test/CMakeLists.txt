cmake_minimum_required(VERSION 3.9)
project(keyboard)

include_directories("../pio/src")
include_directories(".")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_FLAGS “--gmock_verbose=info“)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(googletest)

add_executable(keyboard keyboard.cpp)
target_link_libraries(keyboard gtest gtest_main gmock)