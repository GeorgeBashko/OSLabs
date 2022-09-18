cmake_minimum_required(VERSION 3.23)
project(MainTest)

set(CMAKE_CXX_STANDARD 14)

add_executable(MainTest main.cpp)
add_library(Number STATIC ../Number/cmake-build-debug/libNumber.a ../Number/Number.cpp)
add_library(Vector SHARED ../Vector/cmake-build-debug/libVector.so ../Vector/Vector.cpp)

target_link_libraries(MainTest PUBLIC Number)
target_link_libraries(MainTest PUBLIC Vector)

