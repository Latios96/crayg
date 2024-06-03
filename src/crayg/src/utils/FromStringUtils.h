#pragma once
#include <string>

namespace crayg {

class FromStringUtils {
  public:
    static int parseIntOrThrow(const std::string &str);
};

} // crayg
