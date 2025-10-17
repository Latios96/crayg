#pragma once

#include <filesystem>
#include <string>

namespace crayg {

class ImageChannelPathResolver {
  public:
    std::string resolve(const std::filesystem::path &path, const std::string &channelName);
};

}
