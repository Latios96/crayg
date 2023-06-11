#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_CRAYGMAIN_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_CRAYGMAIN_H_

#define CRAYG_MAIN_IMPL                                                                                                \
    crayg::Logger::initialize();                                                                                       \
    try {                                                                                                              \
        return crayg::craygMain(argc, argv);                                                                           \
    } catch (std::exception & e) {                                                                                     \
        crayg::Logger::backtrace();                                                                                    \
        crayg::Logger::error("Caught exception: {}", e.what());                                                        \
        return -1;                                                                                                     \
    }

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_CRAYGMAIN_H_
