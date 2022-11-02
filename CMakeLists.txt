cmake_minimum_required(VERSION 3.21)
project(Channel)

set(CMAKE_CXX_STANDARD 20)

add_executable(Channel Matrix_buffered_channel.cpp Matrix_buffered_channel.h)
