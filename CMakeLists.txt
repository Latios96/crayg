# cmake_minimum_required(VERSION <specify CMake version here>)
project(crayg)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(crayg
        src/catch.hpp
        src/helloworld.cpp
        .gitignore
        CMakeLists.txt
        README.md)
