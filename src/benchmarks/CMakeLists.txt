add_executable(benchmarks benchmarks.cpp)

target_link_libraries(benchmarks crayg ${CONAN_LIBS})