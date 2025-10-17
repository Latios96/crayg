#pragma once

#include <filesystem>
#include <string>

namespace crayg {

class ImageChannelPathResolver {
  public:
    std::filesystem::path resolve(const std::filesystem::path &path, const std::string &channelName);
};

}
