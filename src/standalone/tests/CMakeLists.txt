set(CRAYG_STANDALONE_TESTS crayg-standalone-tests)

add_executable(${CRAYG_STANDALONE_TESTS}
        main.cpp
        TestArgsParsing.cpp)

target_link_libraries(${CRAYG_STANDALONE_TESTS}
        Main_Lib)

add_test(
        NAME ${CRAYG_STANDALONE_TESTS}
        COMMAND ${CRAYG_STANDALONE_TESTS})