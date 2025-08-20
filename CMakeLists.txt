cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

project(crayg)
set(CMAKE_CXX_STANDARD 20)

enable_testing()

unset(ENV{CI})

set(CONAN_SYSTEM_INCLUDES ON)

option(CRAYG_USE_COMMIT_HASH "Automatically detect the Git commit hash" OFF)
option(CRAYG_ENABLE_TRACING "Enable tracing using Chromium tracing format" OFF)

if(CRAYG_ENABLE_TRACING)
    add_definitions(-DCRAYG_ENABLE_TRACING="ON")
    add_definitions(-DMTR_ENABLED="ON")
endif()

if(CRAYG_USE_COMMIT_HASH)
    execute_process(
        COMMAND git describe --tags
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    add_definitions(-DGIT_COMMIT_HASH="${GIT_COMMIT_HASH}")
else()
    add_definitions(-DGIT_COMMIT_HASH="SNAPSHOT")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/src/cmake/conan.cmake)

set(CMAKE_BUILD_TYPE_FOR_CONAN Release)
if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(CMAKE_BUILD_TYPE_FOR_CONAN Debug)
endif()
message(STATUS "Using BUILD_TYPE=${CMAKE_BUILD_TYPE_FOR_CONAN} for Conan dependencies")

conan_cmake_run(
    CONANFILE
    conanfile.txt
    BASIC_SETUP
    BUILD
    missing
    KEEP_RPATHS
    BUILD_TYPE
    ${CMAKE_BUILD_TYPE_FOR_CONAN})

if(MSVC)
    add_compile_options(
        /wd4305 # double constant assigned to float
        /wd4244 # int -> float conversion
        /wd4267 # size_t -> int conversion
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(CRAYG_DEBUG_BUILD=1)
endif()

add_subdirectory(src)

# Create distribution target
set(CRAYG_EXECUTABLE_EXTENSION "")
set(CRAYG_STANDALONE_EXECUTABLE_EXTENSION "")
if(WIN32)
    set(CRAYG_EXECUTABLE_EXTENSION .exe)
    set(CRAYG_STANDALONE_EXECUTABLE_EXTENSION .exe)
    set(CRAYG_ARCHITECTURE win_amd64)
    set(CRAYG_LIBS_TO_PACKAGE bin/*.dll)
endif()
if(UNIX AND NOT APPLE)
    set(CRAYG_LIBS_TO_PACKAGE ${CRAYG_LIBS_TO_PACKAGE} lib/*.so)
    set(CRAYG_ARCHITECTURE linux)
    set(CRAYG_LIBS_TO_PACKAGE lib/*.so)
endif()
if(APPLE)
    set(CRAYG_STANDALONE_EXECUTABLE_EXTENSION .app)
    set(CRAYG_LIBS_TO_PACKAGE ${CRAYG_LIBS_TO_PACKAGE} lib/*.dylib)
    set(CRAYG_ARCHITECTURE macosx)
    set(CRAYG_LIBS_TO_PACKAGE lib/*.dylib)
endif()
set(CRAYG_EXECUTABLES bin/crayg-standalone${CRAYG_EXECUTABLE_EXTENSION}
                      bin/crayg-standalone-gui${CRAYG_STANDALONE_EXECUTABLE_EXTENSION})
set(CRAYG_PACKAGE_CONTENTS ${CRAYG_EXECUTABLES} ${CRAYG_LIBS_TO_PACKAGE} bin/archdatadir)

add_custom_target(
    createDistribution
    COMMAND tar -czvf "crayg-${GIT_COMMIT_HASH}-${CRAYG_ARCHITECTURE}.tar.gz" -C ${CMAKE_BINARY_DIR}
            ${CRAYG_PACKAGE_CONTENTS}
    DEPENDS crayg crayg-standalone crayg-standalone-gui)
