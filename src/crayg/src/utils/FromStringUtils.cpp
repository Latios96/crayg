#include "FromStringUtils.h"
#include <charconv>
#include <fmt/core.h>
#include <string>

namespace crayg {

int FromStringUtils::parseIntOrThrow(const std::string &str) {
    int result = 0;
    auto [_, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
    if (ec == std::errc::invalid_argument) {
        throw std::runtime_error(fmt::format("Invalid integer: '{}'", str));
    }
    return result;
}

} // crayg