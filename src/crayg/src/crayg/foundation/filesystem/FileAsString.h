#pragma once

#include <string>

namespace crayg {

class FileAsString {
  public:
    static std::string readFileAsString(const std::string &path);
};

}
