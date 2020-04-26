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

set(TBB_OPTIONS "")
if (WIN32)
    set(TBB_OPTIONS TBB:shared=True)
endif ()

conan_cmake_run(REQUIRES
        fmt/5.3.0@bincrafters/stable
        spdlog/1.3.1@bincrafters/stable
        rapidjson/1.1.0@bincrafters/stable
        catch2/2.5.0@bincrafters/stable
        optional-lite/2.3.0@bincrafters/stable
        cli11/1.6.1@bincrafters/stable
        boost/1.72.0
        openimageio/2.1.11.2@ppodsiadly/stable
        TBB/2019_U9@conan/stable
        OPTIONS ${TBB_OPTIONS}
        IMPORTS bin,*.dll->./bin lib,*.dylib*->./bin
        BASIC_SETUP
        BUILD missing)

add_subdirectory(src)
