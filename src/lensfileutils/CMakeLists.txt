add_executable(lensfileutils
        lensfileutils.cpp)

target_link_libraries(lensfileutils crayg ${CONAN_LIBS})

install(TARGETS lensfileutils DESTINATION bin)
