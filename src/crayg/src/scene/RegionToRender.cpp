#include "RegionToRender.h"
#include "utils/Exceptions.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <sstream>

namespace crayg {

RegionToRender::RegionToRender(const PixelRegion &pixelRegion) : region(pixelRegion) {
}

RegionToRender::RegionToRender(const NDCRegion &ndcRegion) : region(ndcRegion) {
}

std::ostream &operator<<(std::ostream &os, const RegionToRender &render) {
    os << render.toString();
    return os;
}

struct RegionToStringVisitor {
    std::string operator()(const PixelRegion &region) {
        return fmt::format("px:[({},{}),({},{})]", region.min.x, region.min.y, region.max.x, region.max.y);
    }

    std::string operator()(const NDCRegion &region) {
        return fmt::format("ndc:[({:.3f},{:.3f}),({:.3f},{:.3f})]", region.min.x, region.min.y, region.max.x,
                           region.max.y);
    }
};

std::string RegionToRender::toString() const {
    return std::visit(RegionToStringVisitor(), region);
}

PixelRegion RegionToRender::toPixelRegion(const Resolution &resolution) const {
    if (isPixelRegion()) {
        return std::get<PixelRegion>(region);
    }
    NDCRegion ndcRegion = std::get<NDCRegion>(region);

    PixelRegion pixelRegion;
    pixelRegion.min.x = ndcRegion.min.x * resolution.getWidth();
    pixelRegion.min.y = resolution.getHeight() - ndcRegion.min.y * resolution.getHeight();
    pixelRegion.max.x = ndcRegion.max.x * resolution.getWidth();
    pixelRegion.max.y = resolution.getHeight() - ndcRegion.max.y * resolution.getHeight();

    return pixelRegion;
}

NDCRegion RegionToRender::toNDCRegion(const Resolution &resolution) const {
    if (isNDCRegion()) {
        return std::get<NDCRegion>(region);
    }

    PixelRegion pixelRegion = std::get<PixelRegion>(region);

    NDCRegion ndcRegion;
    ndcRegion.min.x = static_cast<float>(pixelRegion.min.x) / static_cast<float>(resolution.getWidth());
    ndcRegion.min.y = 1 - static_cast<float>(pixelRegion.min.y) / static_cast<float>(resolution.getHeight());
    ndcRegion.max.x = static_cast<float>(pixelRegion.max.x) / static_cast<float>(resolution.getWidth());
    ndcRegion.max.y = 1 - static_cast<float>(pixelRegion.max.y) / static_cast<float>(resolution.getHeight());
    return ndcRegion;
}

std::string formatParseError(const std::string &str) {
    return fmt::format("Invalid format, expected input in form [(minX, minY),(maxX, maxY)], was {}", str);
}

template <typename T>
Bounds2d<T> parseRegionString(const std::string &str, std::function<T(const std::string &)> parse) {
    // split by , expect 4 values:
    // first: [(number
    // second: number)
    // third: (number
    // forth: number)]

    Bounds2d<T> result;
    std::vector<std::string> splitted;
    boost::split(splitted, str, boost::is_any_of(","));
    if (splitted.size() != 4) {
        CRAYG_LOG_AND_THROW(std::runtime_error(formatParseError(str)));
    }
    if (!boost::algorithm::starts_with(splitted[0], "[(")) {
        CRAYG_LOG_AND_THROW(std::runtime_error(formatParseError(str)));
    }
    T t1 = parse(splitted[0].substr(2));
    result.min.x = t1;

    if (!boost::algorithm::ends_with(splitted[1], ")")) {
        CRAYG_LOG_AND_THROW(std::runtime_error(formatParseError(str)));
    }
    result.min.y = parse(splitted[1].substr(0, splitted[1].size() - 1));

    if (!boost::algorithm::starts_with(splitted[2], "(")) {
        CRAYG_LOG_AND_THROW(std::runtime_error(formatParseError(str)));
    }
    result.max.x = parse(splitted[2].substr(1));

    if (!boost::algorithm::ends_with(splitted[3], ")]")) {
        CRAYG_LOG_AND_THROW(std::runtime_error(formatParseError(str)));
    }
    result.max.y = parse(splitted[3].substr(0, splitted[3].size() - 2));

    return result;
}

RegionToRender RegionToRender::fromString(const std::string &str) {
    const std::string trimmed = boost::algorithm::erase_all_copy(str, " ");
    if (boost::algorithm::starts_with(trimmed, "px:")) {
        const auto region =
            parseRegionString<int>(trimmed.substr(3), [](const std::string &str) { return std::atoi(str.c_str()); });
        return RegionToRender(region);
    } else if (boost::algorithm::starts_with(trimmed, "ndc:")) {
        const auto region = parseRegionString<float>(trimmed.substr(4), [](const std::string &str) {
            std::istringstream iss(str);
            iss.imbue(std::locale::classic());
            float result;
            iss >> result;
            return result;
        });
        return RegionToRender(region);
    } else {
        // invalid
        CRAYG_LOG_AND_THROW(
            std::runtime_error(fmt::format("Invalid format specified, allowed are px and ndc, was '{}'", str)));
    }
}
}