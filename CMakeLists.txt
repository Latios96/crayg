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
        fmt/6.2.0
        spdlog/1.6.0
        rapidjson/1.1.0@bincrafters/stable
        catch2/2.13.2
        optional-lite/2.3.0@bincrafters/stable
        cli11/1.6.1@bincrafters/stable
        boost/1.72.0
        openimageio/2.1.11.2@ppodsiadly/stable
        tinyobjloader/1.0.6
        tbb/2020.2
        qt/5.15.1@bincrafters/stable
        freetype/2.10.2
        IMPORTS bin,*.dll->./bin lib,*.dylib*->./lib lib,*.so*->./lib
        BASIC_SETUP
        BUILD missing
        OPTIONS openimageio:with_jpeg2000=False libtiff:jpeg=libjpeg-turbo qt:with_libjpeg=False
        KEEP_RPATHS
        )



add_subdirectory(src)
