add_executable(matrixgen main.cpp)

target_link_libraries(matrixgen crayg ${CONAN_LIBS} ${CMAKE_DL_LIBS})