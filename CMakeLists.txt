cmake_minimum_required(VERSION 3.22)
project(vt_array LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(test test/test.cxx)
add_executable(bench bench/bench.cxx)