cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(crayg)
set(CMAKE_CXX_STANDARD 14)

option(BUILD_WITH_COVERAGE "Activate --coverage to check for Code Coverage" OFF)

enable_testing()

unset(ENV{CI})

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES
        BASIC_SETUP
        BUILD missing
        KEEP_RPATHS
        SETTINGS arch=x86_64
        )



add_subdirectory(src)
