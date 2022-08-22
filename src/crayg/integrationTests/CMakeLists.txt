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
        COMMAND cato run -u https://cato.frmbffr.com
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

configure_file(cato.json ${CMAKE_BINARY_DIR}/bin/cato.json)