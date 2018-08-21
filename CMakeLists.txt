cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -std=c++11)
project(crayg)

enable_testing()

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(crayg)