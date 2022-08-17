cmake_minimum_required(VERSION 3.22)
project(array LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#add_library(libarray src/internal/type_traits.hpp src/library.cpp)
add_executable(array src/internal/type_traits.hxx src/array.hxx test/test.cxx src/internal/utility.hxx src/internal/numeric.hxx src/internal/size_t.hxx)
