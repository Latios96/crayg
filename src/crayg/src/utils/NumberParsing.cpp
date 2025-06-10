#include "NumberParsing.h"
#include "utils/Exceptions.h"
#include <charconv>
#include <fmt/core.h>
#include <string>

namespace crayg {

int NumberParsing::parseIntOrThrow(const std::string &str) {
    int result = 0;
    auto [_, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
    if (ec == std::errc::invalid_argument) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Invalid integer: '{}'", str);
    }
    return result;
}

} // crayg