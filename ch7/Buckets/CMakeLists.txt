cmake_minimum_required(VERSION 3.24)
project(Buckets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

add_executable(Buckets main.cpp)
