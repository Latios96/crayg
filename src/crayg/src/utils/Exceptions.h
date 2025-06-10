#pragma once
#include <exception>

#define CRAYG_LOG_AND_THROW(exception)                                                                                 \
    logAndThrow(exception, __FILE__, __LINE__);                                                                        \
    throw(exception);

#define CRAYG_LOG_AND_THROW_MESSAGE_NO_FMT(message) CRAYG_LOG_AND_THROW(std::runtime_error(message))
#define CRAYG_LOG_AND_THROW_MESSAGE(formatStr, ...)                                                                    \
    CRAYG_LOG_AND_THROW(std::runtime_error(fmt::format(formatStr, __VA_ARGS__)))

namespace crayg {

void logAndThrow(const std::exception &e, const char *file, int line);

}