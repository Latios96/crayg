cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -std=c++11)
add_compile_options(-std=c++11 -stdlib=libc++ )

project(crayg)

enable_testing()

add_subdirectory(standalone)
add_subdirectory(test)
add_subdirectory(crayg)