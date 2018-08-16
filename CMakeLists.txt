# cmake_minimum_required(VERSION <specify CMake version here>)
project(crayg)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_executable(crayg
        src/crayg.cpp
        .gitignore
        CMakeLists.txt
        README.md src/Image.cpp src/Image.h src/Vector3f.cpp src/Vector3f.h src/Vector3fTests.cpp)
