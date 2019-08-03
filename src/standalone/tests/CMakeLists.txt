set(CRAYG_STANDALONE_TESTS crayg-standalone-tests)

add_executable(${CRAYG_STANDALONE_TESTS}
        main.cpp
        TestArgsParsing.cpp)

add_test(
        NAME ${CRAYG_STANDALONE_TESTS}
        COMMAND ${CRAYG_STANDALONE_TESTS} -o crayg-standalone-tests-report.xml -r junit)