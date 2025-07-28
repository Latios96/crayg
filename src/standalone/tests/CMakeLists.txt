set(CRAYG_STANDALONE_TESTS crayg-standalone-tests)

set(CRAYG_STANDALONE_TESTS_SRC cli/TestArgsParsing.cpp cli/TestCliRenderSettingsOverride.cpp)

add_executable(${CRAYG_STANDALONE_TESTS} # cmake-format: unsortable
               main.cpp ${CRAYG_STANDALONE_TESTS_SRC})
target_link_libraries(${CRAYG_STANDALONE_TESTS} crayg-standalone-lib)

add_test(NAME ${CRAYG_STANDALONE_TESTS} COMMAND ${CRAYG_STANDALONE_TESTS})
