add_executable(knipser-test-testregistration TestTestRegistration.cpp)

target_link_libraries(knipser-test-testregistration
        ${CONAN_LIBS} knipser)

add_test(
        NAME knipser-test-testregistration
        COMMAND ${CRAYG_STANDALONE_TESTS} -o crayg-standalone-tests-report.xml -r junit)