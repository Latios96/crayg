#pragma once

#include <string>

namespace crayg {

class ImageChannelPathResolver {
  public:
    std::string resolve(const std::string &path, const std::string &channelName);
};

} // crayg
