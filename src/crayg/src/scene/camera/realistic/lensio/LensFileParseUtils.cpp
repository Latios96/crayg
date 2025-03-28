#include "LensFileParseUtils.h"
#include "utils/Exceptions.h"
#include <fmt/format.h>

namespace crayg {

InvalidLensFileException::InvalidLensFileException(const std::string &message)
    : runtime_error(fmt::format("Invalid lens file: {}", message)) {
}

InvalidLensFileException::InvalidLensFileException(int lineIndex, const std::string &message)
    : runtime_error(fmt::format("Invalid lens file: Line {}: {}", lineIndex + 1, message)) {
}

float LensFileParseUtils::parseFloat(int lineIndex, const std::string &floatStr, const std::string &name) {
    try {
        return std::stof(floatStr);
    } catch (std::invalid_argument &e) {
        CRAYG_LOG_AND_THROW(
            InvalidLensFileException(lineIndex, fmt::format("Value '{}' for {} is not a float", floatStr, name)));
    }
}

int LensFileParseUtils::parseInt(int lineIndex, const std::string &intStr, const std::string &name) {
    try {
        return std::stoi(intStr);
    } catch (std::invalid_argument &e) {
        CRAYG_LOG_AND_THROW(
            InvalidLensFileException(lineIndex, fmt::format("Value '{}' for {} is not a int", intStr, name)));
    }
}

}