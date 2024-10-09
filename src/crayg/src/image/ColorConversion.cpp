#include "ColorConversion.h"
#include "imageiterators/pixels/ImageIterators.h"
#include "utils/tracing/CraygTracing.h"

namespace crayg {

bool ColorConversion::channelNeedsLinearToSRgbConversion(const std::string &channelName) {
    return channelName == "rgb";
}

void ColorConversion::linearToSRGB(const PixelBuffer &source, PixelBuffer &target) {
    CRG_TRACE_SCOPE("ColorConversion");
    for (auto pixel : ImageIterators::lineByLine(source)) {
        target.setValue(pixel, linearToSRGB(source.getValue(pixel)));
    }
}

Color ColorConversion::linearToSRGB(const Color &color) {
    static const float gamma = 1.0f / 2.2f;
    return color.pow(gamma);
}

}