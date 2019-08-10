add_executable(knipser-test-testregistration TestTestRegistration.cpp)

target_link_libraries(knipser-test-testregistration
        ${CONAN_LIBS} knipser)

add_test(
        NAME knipser-test-testregistration
        COMMAND knipser-test-testregistration -o knipser-test-testregistration-report.xml -r junit)

add_executable(knipser-test-testrunner TestTestRunner.cpp)

target_link_libraries(knipser-test-testrunner
        ${CONAN_LIBS} knipser)

add_test(
        NAME knipser-test-testrunner
        COMMAND knipser-test-testrunner -o knipser-test-testrunner-report.xml -r junit)