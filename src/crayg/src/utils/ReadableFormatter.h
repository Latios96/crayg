#pragma once

#include <chrono>
#include <string>

namespace crayg {

class ReadableFormatter {
  public:
    std::string formatDuration(std::chrono::seconds seconds);
};
}
