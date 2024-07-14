#pragma once
#include <exception>

#define CRAYG_LOG_AND_THROW(exception)                                                                                 \
    logAndThrow(exception, __FILE__, __LINE__);                                                                        \
    throw(exception);

#define CRAYG_LOG_AND_THROW_MESSAGE(message) CRAYG_LOG_AND_THROW(std::runtime_error(message))

namespace crayg {

void logAndThrow(const std::exception &e, const char *file, int line);

}