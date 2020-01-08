set(CRAYG_STANDALONE_LIB crayg-standalone-lib)

set(CRAYG_STANDALONE_LIB_SRCS
        CliParser.h
        CliParser.cpp)

set(Main_Executable_SRCS
        main.cpp)

add_library(Main_Lib STATIC ${CRAYG_STANDALONE_LIB_SRCS})

add_executable(crayg-standalone
        ${Main_Executable_SRCS})


target_link_libraries(crayg-standalone
        Main_Lib)

target_link_libraries(Main_Lib
        crayg)

target_include_directories(Main_Lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

#set_target_properties(crayg-standalone
#        PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} --coverage"
#        LINK_FLAGS "--coverage")


install(TARGETS crayg-standalone DESTINATION bin)
