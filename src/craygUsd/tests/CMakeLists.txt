
set(TARGET_NAME crayg_usd_tests)

add_executable(${TARGET_NAME}
        main.cpp
        TestUsdCameraTranslator.cpp
        TestUsdConversions.cpp
        TestUsdMeshTranslator.cpp
        )

target_link_libraries(${TARGET_NAME}
        PUBLIC crayg_usd)

add_test(
        NAME ${TARGET_NAME}
        COMMAND ${TARGET_NAME} --durations yes)