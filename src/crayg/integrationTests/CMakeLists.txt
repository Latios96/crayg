add_executable(crayg-integration-tests main.cpp)
target_link_libraries(crayg-integration-tests crayg knipser)

add_test(
        NAME crayg-integration-tests
        COMMAND crayg-integration-tests --output knipser-output --reference ${CMAKE_CURRENT_SOURCE_DIR}/reference
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)