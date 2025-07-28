#pragma once
#include <string>

namespace crayg {

class NumberParsing {
  public:
    static int parseIntOrThrow(const std::string &str);
};

}
