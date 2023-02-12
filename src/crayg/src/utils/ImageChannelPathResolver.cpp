#include "ImageChannelPathResolver.h"
#include <boost/filesystem/path.hpp>
#include <boost/regex.hpp>
#include <fmt/format.h>

namespace crayg {
std::string ImageChannelPathResolver::resolve(const std::string &path, const std::string &channelName) {
    if (channelName == "rgb") {
        return path;
    }

    auto boostPath = boost::filesystem::path(path);
    auto pathWithoutExtension = boostPath.parent_path() / boostPath.stem();
    const boost::filesystem::path &hashOrDigits = pathWithoutExtension.extension();
    if (hashOrDigits == ".#" || boost::regex_match(hashOrDigits.string(), boost::regex("\\.\\d+"))) {
        pathWithoutExtension = pathWithoutExtension.parent_path() / pathWithoutExtension.stem();
    }

    return fmt::format("{}.{}{}{}",
                       pathWithoutExtension.string(),
                       channelName,
                       hashOrDigits.string(),
                       boostPath.extension().string());
}
} // crayg