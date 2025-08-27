#pragma once

#include <filesystem>

namespace crayg {

class ImagePathResolver {
  public:
    static std::filesystem::path resolve(const std::filesystem::path &pathTemplate);
    static int parseImageNumber(const std::filesystem::path &path);
    static bool matchesTemplate(const std::filesystem::path &pathTemplate, const std::filesystem::path &path);
};

}
