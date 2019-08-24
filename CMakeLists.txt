cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(crayg)
set(CMAKE_CXX_STANDARD 11)

enable_testing()
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

execute_process(COMMAND conan create . Latios/stable --build missing
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/conan_packages/openexr)

execute_process(COMMAND conan create . Latios/stable --build missing
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/conan_packages/OpenImageIO)

conan_cmake_run(REQUIRES fmt/5.3.0@bincrafters/stable
        spdlog/1.3.1@bincrafters/stable
        rapidjson/1.1.0@bincrafters/stable
        catch2/2.5.0@bincrafters/stable
        optional-lite/2.3.0@bincrafters/stable
        cli11/1.6.1@bincrafters/stable
        boost/1.70.0@conan/stable
        OpenImageIO/2.0.3@Latios/stable
        openexr/2.3.0@Latios/stable

        BASIC_SETUP
        BUILD missing)

add_subdirectory(src)