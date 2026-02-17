cmake_minimum_required(VERSION 4.0)
project(cpp_oop)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cpp_oop
        main_rational.cpp
        rational.cpp
        rational.h)
