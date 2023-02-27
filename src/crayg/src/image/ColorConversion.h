#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_COLORCONVERSION_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_COLORCONVERSION_H_

#include "PixelBuffer.h"
#include "basics/Color.h"

namespace crayg {

class ColorConversion {
  public:
    static bool channelNeedsLinearToSRgbConversion(const std::string &channelName);
    static Color linearToSRGB(const Color &color);
    static void linearToSRGB(const PixelBuffer &source, PixelBuffer &target);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_COLORCONVERSION_H_
