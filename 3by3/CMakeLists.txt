cmake_minimum_required(VERSION 3.10)
project(2by2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(solve state.cpp 3by3.cpp)

