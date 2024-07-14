#include "Logger.h"
#include <cpptrace/cpptrace.hpp>

namespace crayg {

void logAndThrow(const std::exception &e, const char *file, int line) {
    const auto raw_trace = cpptrace::generate_raw_trace();
    Logger::error("Error at {}:{}: {}\n{}", file, line, (e.what()), raw_trace.resolve().to_string());
}
}