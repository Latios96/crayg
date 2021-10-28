add_executable(usdexplorations main.cpp TriangleMeshBuilder.cpp TriangleMeshBuilder.h)

target_link_libraries(usdexplorations crayg ${CONAN_LIBS} ${CMAKE_DL_LIBS} hd)