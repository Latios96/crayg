add_library(knipser
        STATIC
        TestRegistry.h
        TestRegistry.cpp
        KnipserTest.h
        KnipserTest.cpp
        TestContext.h
        TestContext.cpp
        TestRunner.h
        TestRunner.cpp
        ReportGenerator.h
        ReportGenerator.cpp
        TestResult.h
        TestResult.cpp
        PlainReportGenerator.h
        PlainReportGenerator.cpp
        RunConfig.h
        RunConfig.cpp
        KnipserAssertions.h
        KnipserAssertions.cpp
        ImageComparator.h
        ImageComparator.cpp
        KnipserApp.h
        KnipserApp.cpp
        TestPattern.h
        TestPattern.cpp
        TestPatternStringParser.h
        TestPatternStringParser.cpp)


target_include_directories(knipser PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(knipser ${CONAN_LIBS} dl)

add_executable(knipser-main main.cpp)
target_link_libraries(knipser-main knipser)
install(TARGETS knipser-main DESTINATION bin)