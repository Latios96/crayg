#include "ImageChannelPathResolver.h"
#include <boost/regex.hpp>
#include <filesystem>
#include <fmt/format.h>

namespace crayg {
std::string ImageChannelPathResolver::resolve(const std::filesystem::path &path, const std::string &channelName) {
    if (channelName == "rgb") {
        return path;
    }

    auto pathWithoutExtension = path.parent_path() / path.stem();
    const std::filesystem::path &hashOrDigits = pathWithoutExtension.extension();
    if (hashOrDigits == ".#" || boost::regex_match(hashOrDigits.string(), boost::regex("\\.\\d+"))) {
        pathWithoutExtension = pathWithoutExtension.parent_path() / pathWithoutExtension.stem();
    }

    return fmt::format("{}.{}{}{}", pathWithoutExtension.string(), channelName, hashOrDigits.string(),
                       path.extension().string());
}
}