# own executable for test registration, since we access the global TestRegistry here

add_executable(knipser-main-tests TestTestRunner.cpp
        TestTestResult.cpp
        TestPlainReportGenerator.cpp
        TestTestContext.cpp
        TestAssertions.cpp
        TestImageComparator.cpp
        TestTestPattern.cpp
        TestTestPatternStringParser.cpp
        TestExecuteTestPredicate.cpp
        KnipserTestUtils.h
        KnipserTestUtils.cpp
        TestTestRegistration.cpp
        main.cpp)

target_link_libraries(knipser-main-tests
        ${CONAN_LIBS} knipser)

add_test(
        NAME knipser-main-tests
        COMMAND knipser-main-tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

function(add_test_resource target_name absolute_path)
    message("add_test_resource " ${target_name})
    get_filename_component(file_name ${absolute_path} NAME)
    message("add_test_resource " ${CMAKE_COMMAND} -E copy ${absolute_path} $<TARGET_FILE_DIR:${target_name}>/${file_name})
    add_custom_command(TARGET ${target_name} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${absolute_path} $<TARGET_FILE_DIR:${target_name}>/${file_name})
endfunction(add_test_resource)

add_test_resource(knipser-main-tests ${CMAKE_CURRENT_SOURCE_DIR}/test_image_black.png)
add_test_resource(knipser-main-tests ${CMAKE_CURRENT_SOURCE_DIR}/test_image_white.png)