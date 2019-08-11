# own executable for test registration, since we access the global TestRegistry here
add_executable(knipser-test-testregistration TestTestRegistration.cpp)
target_link_libraries(knipser-test-testregistration
        ${CONAN_LIBS} knipser)
add_test(
        NAME knipser-test-testregistration
        COMMAND knipser-test-testregistration -o knipser-test-testregistration-report.xml -r junit)


add_executable(knipser-main-tests TestTestRunner.cpp
        TestTestResult.cpp
        TestPlainReportGenerator.cpp
        main.cpp)

target_link_libraries(knipser-main-tests
        ${CONAN_LIBS} knipser)

add_test(
        NAME knipser-main-tests
        COMMAND knipser-main-tests -o knipser-main-tests-report.xml -r junit)
