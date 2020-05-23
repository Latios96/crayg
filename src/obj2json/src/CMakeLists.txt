add_executable(obj2json main.cpp)

target_link_libraries(obj2json crayg ${CONAN_LIBS} ${CMAKE_DL_LIBS})