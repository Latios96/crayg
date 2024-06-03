#pragma once
#include "Logger.h"
#include <cpptrace/cpptrace.hpp>

#define CRAYG_LOG_AND_THROW(exception)                                                                                 \
    const auto raw_trace = cpptrace::generate_raw_trace();                                                             \
    Logger::error("Error at {}:{}: {}\n{}", __FILE__, __LINE__, (exception.what()), raw_trace.resolve().to_string());  \
    throw(exception);

#define CRAYG_LOG_AND_THROW_MESSAGE(message) CRAYG_LOG_AND_THROW(std::runtime_error(message))
