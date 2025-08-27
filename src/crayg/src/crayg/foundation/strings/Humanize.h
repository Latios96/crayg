#pragma once
#include <chrono>
#include <string>

namespace crayg {

class Humanize {
  public:
    static std::string naturalFileSize(size_t bytes);
    static std::string naturalDuration(std::chrono::seconds seconds);
};

}