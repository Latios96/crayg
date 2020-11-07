add_executable(benchmarks benchmarks.cpp)

find_library(SHLWAPI Shlwapi.lib)
target_link_libraries(benchmarks crayg ${SHLWAPI} ${CONAN_LIBS})