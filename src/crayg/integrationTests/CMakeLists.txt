add_executable(crayg-binary-integration-tests
        main.cpp
        imageTests.cpp
        sceneIO.cpp
        renderUtils.h
        renderUtils.cpp
        utils.h
        utils.cpp
        )

target_link_libraries(crayg-binary-integration-tests crayg)

add_test(
        NAME crayg-integration-tests
        COMMAND cato run --var crayg_bin_folder=${CMAKE_BINARY_DIR}/bin
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})