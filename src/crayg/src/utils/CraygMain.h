#pragma once

#define CRAYG_MAIN_IMPL                                                                                                \
    crayg::Logger::initialize();                                                                                       \
    try {                                                                                                              \
        return crayg::craygMain(argc, argv);                                                                           \
    } catch (std::exception & e) {                                                                                     \
        crayg::Logger::backtrace();                                                                                    \
        crayg::Logger::error("Caught exception: {}", e.what());                                                        \
        return -1;                                                                                                     \
    }
