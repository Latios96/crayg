#include "ImageChannelPathResolver.h"
#include <boost/regex.hpp>
#include <fmt/format.h>

namespace crayg {
std::string ImageChannelPathResolver::resolve(const std::string &path, const std::string &channelName) {
    if (channelName == "rgb") {
        return path;
    }

    auto boostPath = boost::filesystem::path(path);
    auto pathWithoutExtension = boostPath.stem();
    const boost::filesystem::path &hashOrDigits = pathWithoutExtension.extension();
    if (hashOrDigits == ".#" || boost::regex_match(hashOrDigits.string(), boost::regex("\\.\\d+"))) {
        pathWithoutExtension = pathWithoutExtension.stem();
    }

    return fmt::format("{}.{}{}{}",
                       pathWithoutExtension.string(),
                       channelName,
                       hashOrDigits.string(),
                       boostPath.extension().string());
}
} // crayg