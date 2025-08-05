set(INTEGRATION_TEST_SRCS
    ImageAndFilmFixture.h
    imageTests.cpp
    pngImageFormatWriter.cpp
    renderUtils.cpp
    renderUtils.h
    sceneIO.cpp
    utils.cpp
    utils.h)

add_executable(crayg-binary-integration-tests # cmake-format: unsortable
               main.cpp ${INTEGRATION_TEST_SRCS})

target_link_libraries(crayg-binary-integration-tests crayg)

add_test(
    NAME crayg-integration-tests
    COMMAND cato run --var crayg_bin_folder=${CMAKE_BINARY_DIR}/bin
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
