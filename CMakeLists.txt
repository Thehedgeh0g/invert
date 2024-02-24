cmake_minimum_required(VERSION 3.27)
project(invert)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(invert main.cpp)
