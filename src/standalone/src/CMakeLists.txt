set(CRAYG_STANDALONE_LIB crayg-standalone-lib)

set(CRAYG_STANDALONE_LIB_SRCS
    crayg_standalone/cli/CliParser.cpp crayg_standalone/cli/CliParser.h
    crayg_standalone/cli/CliRenderSettingsOverride.cpp crayg_standalone/cli/CliRenderSettingsOverride.h)

set(Main_Executable_SRCS main.cpp)

add_library(${CRAYG_STANDALONE_LIB} STATIC ${CRAYG_STANDALONE_LIB_SRCS})

add_executable(crayg-standalone ${Main_Executable_SRCS})

target_link_libraries(crayg-standalone ${CRAYG_STANDALONE_LIB})

target_link_libraries(${CRAYG_STANDALONE_LIB} crayg)

target_include_directories(${CRAYG_STANDALONE_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS crayg-standalone DESTINATION bin)
