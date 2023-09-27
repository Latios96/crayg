#include "Resolution.h"
#include "utils/Exceptions.h"
#include "utils/FromStringUtils.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fmt/format.h>
#include <vector>

namespace crayg {

Resolution::Resolution(int width, int height) : width(width), height(height) {
}

bool Resolution::operator==(const Resolution &rhs) const {
    return width == rhs.width && height == rhs.height;
}

bool Resolution::operator!=(const Resolution &rhs) const {
    return !(rhs == *this);
}

bool Resolution::operator<(const Resolution &rhs) const {
    if (width < rhs.width) {
        return true;
    }
    if (rhs.width < width) {
        return false;
    }
    return height < rhs.height;
}

bool Resolution::operator>(const Resolution &rhs) const {
    return rhs < *this;
}

bool Resolution::operator<=(const Resolution &rhs) const {
    return !(rhs < *this);
}

bool Resolution::operator>=(const Resolution &rhs) const {
    return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &os, const Resolution &resolution) {
    os << fmt::format("{}x{}", resolution.width, resolution.height);
    return os;
}

Resolution::Resolution() : width(0), height(0) {
}

int Resolution::getWidth() const {
    return width;
}

int Resolution::getHeight() const {
    return height;
}

Resolution::Resolution(const Resolution &resolution) : width(resolution.width), height(resolution.height) {
}

Resolution Resolution::parse(const std::string &resolutionString) {
    const std::runtime_error error =
        std::runtime_error(fmt::format("Resolution string '{}' has invalid format", resolutionString));
    std::vector<std::string> splitResults;
    boost::algorithm::split(splitResults, resolutionString, boost::algorithm::is_any_of("x"));
    if (splitResults.size() != 2 || splitResults.size() == 2 && (splitResults[0].empty() || splitResults[1].empty())) {
        CRAYG_LOG_AND_THROW(error);
    }

    int width = 0;
    int height = 0;
    try {
        width = FromStringUtils::parseIntOrThrow(splitResults[0]);
        height = FromStringUtils::parseIntOrThrow(splitResults[1]);
    } catch (std::runtime_error &e) {
        CRAYG_LOG_AND_THROW(error);
    }

    if (width < 0) {
        CRAYG_LOG_AND_THROW(
            std::runtime_error(fmt::format("Invalid resolution string '{}', width needs to be >=0", resolutionString)));
    }
    if (height < 0) {
        CRAYG_LOG_AND_THROW(
            std::runtime_error(fmt::format("Invalid resolution string '{}', width needs to be >=0", resolutionString)));
    }

    return {width, height};
}

}
