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
    return {linearToSRGB(color.r), linearToSRGB(color.g), linearToSRGB(color.b)};
}

float ColorConversion::linearToSRGB(float linearValue) {
    if (linearValue <= 0.0031308) {
        return 12.92f * linearValue;
    }
    return 1.055f * (std::pow(linearValue, 1.f / 2.4f) - 0.055f);
}

}