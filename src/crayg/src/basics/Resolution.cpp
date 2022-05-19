//
// Created by Jan on 30.10.2020.
//

#include <fmt/format.h>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "Resolution.h"

namespace crayg {

Resolution::Resolution(int width, int height) : width(width), height(height) {}
bool Resolution::operator==(const Resolution &rhs) const {
    return width == rhs.width &&
        height == rhs.height;
}
bool Resolution::operator!=(const Resolution &rhs) const {
    return !(rhs == *this);
}
bool Resolution::operator<(const Resolution &rhs) const {
    if (width < rhs.width)
        return true;
    if (rhs.width < width)
        return false;
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
const int Resolution::getWidth() const {
    return width;
}
const int Resolution::getHeight() const {
    return height;
}
Resolution::Resolution(const Resolution &resolution) : width(resolution.width), height(resolution.height) {

}
Resolution Resolution::parse(const std::string &resolutionString) {
    std::vector<std::string> splitResults;
    boost::algorithm::split(splitResults, resolutionString, boost::algorithm::is_any_of("x"));
    if (splitResults.size() != 2 || splitResults.size() == 2 && (splitResults[0].empty() || splitResults[1].empty())) {
        throw std::runtime_error(fmt::format("Resolution string {} has invalid format", resolutionString));
    }
    return {std::atoi(splitResults[0].c_str()), std::atoi(splitResults[1].c_str())};
}

}
