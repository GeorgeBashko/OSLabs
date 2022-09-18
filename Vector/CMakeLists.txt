cmake_minimum_required(VERSION 3.23)
project(Vector)

set(CMAKE_CXX_STANDARD 14)

add_library(Number ../Number/cmake-build-debug/libNumber.a ../Number/Number.cpp)

add_library(Vector SHARED Vector.cpp)

target_link_directories(Vector PUBLIC Vector.cpp Vector.h)
