cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

project(crayg)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

unset(ENV{CI})

set(CONAN_SYSTEM_INCLUDES ON)

option(CRAYG_USE_COMMIT_HASH "Automatically detect the Git commit hash" OFF)

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

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
         "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

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

# for some reasons we can not link against this under Ubuntu-20.04
list(REMOVE_ITEM CONAN_LIBS "Qt5XcbQpa")

if(MSVC)
    add_compile_options(
        /wd4305 # double constant assigned to float
        /wd4244 # int -> float conversion
        /wd4267 # size_t -> int conversion
    )
endif()

# Note: cpptrace has no Conan package so far and creating one is too much work for now..
include(FetchContent)
FetchContent_Declare(
    cpptrace
    GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
    GIT_TAG v0.2.0-beta2 # <HASH or TAG>
)
FetchContent_MakeAvailable(cpptrace)
set(cpptrace_targets cpptrace)
if(TARGET dwarf)
    list(APPEND cpptrace_targets dwarf)
endif()
set_target_properties(${cpptrace_targets} PROPERTIES UNITY_BUILD OFF)

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
