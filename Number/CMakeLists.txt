cmake_minimum_required(VERSION 3.23)
project(Number)

set(CMAKE_CXX_STANDARD 14)

set(NUMBER_HEADER Number.h)
set(NUMBER_SOURCE Number.cpp)
add_library(Number STATIC ${NUMBER_SOURCE} ${NUMBER_HEADER})