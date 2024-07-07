#pragma once

#include <string>

namespace crayg {

class FileSystemUtils {
  public:
    static std::string swapFileExtension(const std::string &path, const std::string &newExtension);
    static std::string readFileAsString(const std::string &path);
};

} // crayg
