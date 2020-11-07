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

conan_cmake_run(CONANFILE conanfile.txt
        BASIC_SETUP
        BUILD missing
        KEEP_RPATHS)

add_subdirectory(src)


set(CRAYG_EXECUTABLE_EXTENSION "")
if (WIN32)
    set(CRAYG_EXECUTABLE_EXTENSION .exe)
    set(CRAYG_ARCHITECTURE win_amd64)
endif ()
if (UNIX AND NOT APPLE)
    set(CRAYG_LIBS_TO_PACKAGE ${CRAYG_LIBS_TO_PACKAGE} lib/*.so)
    set(CRAYG_ARCHITECTURE linux)
endif ()
if (APPLE)
    set(CRAYG_LIBS_TO_PACKAGE ${CRAYG_LIBS_TO_PACKAGE} lib/*.dylib)
    set(CRAYG_ARCHITECTURE macosx)
endif ()
set(CRAYG_EXECUTABLES bin/crayg-standalone${CRAYG_EXECUTABLE_EXTENSION} bin/standalone-gui${CRAYG_EXECUTABLE_EXTENSION} bin/obj2json${CRAYG_EXECUTABLE_EXTENSION})
set(CRAYG_LIBS_TO_PACKAGE bin/*.dll)
set(CRAYG_PACKAGE_CONTENTS ${CRAYG_EXECUTABLES} ${CRAYG_LIBS_TO_PACKAGE} bin/qt.conf bin/plugins)


add_custom_target(createDistribution
        COMMAND tar -czvf "crayg-${CRAYG_ARCHITECTURE}.tar.gz" -C ${CMAKE_BINARY_DIR} ${CRAYG_PACKAGE_CONTENTS}
        DEPENDS crayg crayg-standalone standalone-gui obj2json)
