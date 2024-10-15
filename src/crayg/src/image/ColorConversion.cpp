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

float ColorConversion::linearToSRGB(float linearValue) {
    if (linearValue <= 0.0031308) {
        return 12.92f * linearValue;
    }
    return 1.055f * (std::pow(linearValue, 1.f / 2.4f) - 0.055f);
}

Color ColorConversion::linearToSRGB(const Color &color) {
    return {linearToSRGB(color.r), linearToSRGB(color.g), linearToSRGB(color.b)};
}

void ColorConversion::sRGBToLinear(const PixelBuffer &source, PixelBuffer &target) {
    CRG_TRACE_SCOPE("ColorConversion");
    for (auto pixel : ImageIterators::lineByLine(source)) {
        target.setValue(pixel, sRGBToLinear(source.getValue(pixel)));
    }
}

Color ColorConversion::sRGBToLinear(const Color &color) {
    return {sRGBToLinear(color.r), linearToSRGB(color.g), linearToSRGB(color.b)};
}

float ColorConversion::sRGBToLinear(float sRGBValue) {
    if (sRGBValue <= 0.04045f) {
        return sRGBValue / 12.92f;
    } else {
        return std::pow(((sRGBValue + 0.055f) / 1.055f), 2.4f);
    }
}

}