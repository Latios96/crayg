#include "LensFileParseUtils.h"
#include "utils/Exceptions.h"
#include <fmt/format.h>
#include <charconv>

namespace crayg {

InvalidLensFileException::InvalidLensFileException(const std::string &message)
    : runtime_error(fmt::format("Invalid lens file: {}", message)) {
}

InvalidLensFileException::InvalidLensFileException(int lineIndex, const std::string &message)
    : runtime_error(fmt::format("Invalid lens file: Line {}: {}", lineIndex + 1, message)) {
}

float LensFileParseUtils::parseFloat(int lineIndex, const std::string &floatStr, const std::string &name) {
    float value;
    const auto [ptr, errc] = std::from_chars(floatStr.data(), floatStr.data() + floatStr.size(), value);

    if (errc == std::errc()) {
        return value;
    }

    CRAYG_LOG_AND_THROW(
        InvalidLensFileException(lineIndex, fmt::format("Value '{}' for {} is not a float", floatStr, name)));
}

int LensFileParseUtils::parseInt(int lineIndex, const std::string &intStr, const std::string &name) {
    int value;
    const auto [ptr, errc] = std::from_chars(intStr.data(), intStr.data() + intStr.size(), value);

    if (errc == std::errc()) {
        return value;
    }

    CRAYG_LOG_AND_THROW(
        InvalidLensFileException(lineIndex, fmt::format("Value '{}' for {} is not an int", intStr, name)));
}

}