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
        ImageComparator.cpp)


target_include_directories(knipser PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_include_directories(knipser
        PUBLIC ../../externals/ghc)

target_link_libraries(knipser ${CONAN_LIBS})