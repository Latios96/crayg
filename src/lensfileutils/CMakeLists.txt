add_executable(lensfileutils lensfileutils.cpp)

target_link_libraries(lensfileutils crayg ${CONAN_LIBS})

install(TARGETS lensfileutils DESTINATION bin)

add_executable(lensfileembedder lensfileembedder.cpp)

target_link_libraries(lensfileembedder crayg ${CONAN_LIBS})

install(TARGETS lensfileembedder DESTINATION bin)
