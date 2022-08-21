add_executable(crayg-integration-tests
        main.cpp
        imageTests.h
        renderTests.h
        renderTestsCato.h
        sceneIO.h
        renderUtils.h
        renderUtils.cpp)

target_link_libraries(crayg-integration-tests crayg knipser)

add_test(
        NAME crayg-integration-tests
        COMMAND crayg-integration-tests --output knipser-output --reference ${CMAKE_CURRENT_SOURCE_DIR}/reference
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_test(
        NAME crayg-cato-integration-tests
        COMMAND cato run -u https://cato.frmbffr.com
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

configure_file(cato.json ${CMAKE_BINARY_DIR}/bin/cato.json)