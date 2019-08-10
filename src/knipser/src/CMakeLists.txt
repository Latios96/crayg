add_library(knipser
        STATIC
        TestRegistry.h
        TestRegistry.cpp
        KnipserTest.h
        KnipserTest.cpp
        TestContext.h
        TestContext.cpp
        TestRunner.h
        TestRunner.cpp)


target_include_directories(knipser PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )