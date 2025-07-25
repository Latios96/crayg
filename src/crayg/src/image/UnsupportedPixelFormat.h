#pragma once
#include "PixelFormat.h"
#include <fmt/format.h>

#include <stdexcept>

namespace crayg {

class UnsupportedPixelFormat : public std::runtime_error {
  public:
    explicit UnsupportedPixelFormat(PixelFormat pixelFormat)
        : std::runtime_error(fmt::format("Unsupported pixel format {}", pixelFormat)) {
    }
};

}
