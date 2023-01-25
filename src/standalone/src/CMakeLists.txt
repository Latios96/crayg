set(CRAYG_STANDALONE_LIB crayg-standalone-lib)

set(CRAYG_STANDALONE_LIB_SRCS
        CliParser.cpp
        CliParser.h
        CliRenderSettingsOverride.cpp
        CliRenderSettingsOverride.h
        )

set(Main_Executable_SRCS
        main.cpp)

add_library(${CRAYG_STANDALONE_LIB} STATIC ${CRAYG_STANDALONE_LIB_SRCS})

add_executable(crayg-standalone
        ${Main_Executable_SRCS})


target_link_libraries(crayg-standalone
        ${CRAYG_STANDALONE_LIB})

target_link_libraries(${CRAYG_STANDALONE_LIB}
        crayg)

target_include_directories(${CRAYG_STANDALONE_LIB} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

if (${BUILD_WITH_COVERAGE})
    set_target_properties(crayg-standalone
            PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} --coverage"
            LINK_FLAGS "--coverage")
endif ()


install(TARGETS crayg-standalone DESTINATION bin)

add_executable(osd-experiments
        osd-experiments.cpp)
target_link_libraries(osd-experiments
        ${CRAYG_STANDALONE_LIB})
install(TARGETS osd-experiments DESTINATION bin)
