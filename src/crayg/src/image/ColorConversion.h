#pragma once

#include "PixelBuffer.h"
#include "basics/Color.h"

namespace crayg {

class ColorConversion {
  public:
    static bool channelNeedsLinearToSRgbConversion(const std::string &channelName);
    static float linearToSRGB(float linearValue);
    static Color linearToSRGB(const Color &color);
    static void linearToSRGB(const PixelBuffer &source, PixelBuffer &target);
};

} // crayg
