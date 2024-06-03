#pragma once

#include <chrono>
#include <string>

class ReadableFormatter {
  public:
    std::string formatDuration(std::chrono::seconds seconds);
};
