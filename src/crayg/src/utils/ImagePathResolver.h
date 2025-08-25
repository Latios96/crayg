#pragma once

#include <filesystem>

namespace crayg {

class ImagePathResolver {
  public:
    std::filesystem::path resolve(const std::filesystem::path &pathTemplate) const;
    int parseImageNumber(const std::filesystem::path &path) const;
    bool matchesTemplate(const std::filesystem::path &pathTemplate, const std::filesystem::path &path) const;
};

}
