cmake_minimum_required(VERSION 3.22)
project(vt_array LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#To compile as library use
#add_library(
add_executable(
vt_array
        src/internal/size_t.hxx
        src/internal/numeric.hxx
        src/internal/utility.hxx
        src/internal/type_traits.hxx
        src/array.hxx
        test/test.cxx
)
