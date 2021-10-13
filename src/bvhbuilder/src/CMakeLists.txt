add_executable(bvhbuilder main.cpp)

target_link_libraries(bvhbuilder crayg ${CONAN_LIBS} ${CMAKE_DL_LIBS})