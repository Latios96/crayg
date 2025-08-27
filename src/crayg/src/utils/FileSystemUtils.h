#pragma once

#include <string>

namespace crayg {

class FileSystemUtils {
  public:
    static std::string readFileAsString(const std::string &path);
};

}
