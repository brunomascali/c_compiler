cmake_minimum_required(VERSION 4.1)
project(c_compiler)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)
target_include_directories(c_compiler PRIVATE src)