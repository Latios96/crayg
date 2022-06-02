add_executable(jsonsceneconverter main.cpp)

target_link_libraries(jsonsceneconverter crayg ${CONAN_LIBS} ${CMAKE_DL_LIBS})