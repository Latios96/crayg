#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_EXCEPTIONS_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_EXCEPTIONS_H_
#include "Logger.h"
#include <cpptrace/cpptrace.hpp>

#define CRAYG_LOG_AND_THROW(exception)                                                                                 \
    const auto raw_trace = cpptrace::generate_raw_trace();                                                             \
    Logger::error("Error at {}:{}: {}\n{}", __FILE__, __LINE__, (exception.what()), raw_trace.resolve().to_string());  \
    throw(exception);

#define CRAYG_LOG_AND_THROW_MESSAGE(message) CRAYG_LOG_AND_THROW(std::runtime_error(message))

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_EXCEPTIONS_H_
