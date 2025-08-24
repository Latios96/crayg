#pragma once

#include "Image.h"
#include "ImageTile.h"
#include "basics/Gradient.h"
#include "crayg/foundation/areaiterators/AreaIterators.h"

namespace crayg {

class ImageAlgorithms {
  public:
    static void copyTileImageBufferIntoImage(const ImageTile &imageTile, Image &image);
    static void copyTileImageBufferIntoImage(const ImageTile &imageTile, Image &image,
                                             const std::vector<std::string> &channelsToUpdate);
    static void updateChannel(Image &image, const std::string &channelName, PixelBuffer *pixelBuffer);

    template <typename I> static void fill(I &image, const Color &color) {
        for (auto pixel : AreaIterators::scanlines(image)) {
            image.setValue(pixel, color);
        }
    }

    template <typename I> static void fill(I &image, const Color &color, const Tile &region) {
        const bool isContained = tileIsContainedInImage(region, image);

        if (!isContained) {
            return;
        }

        for (auto pixel : AreaIterators::scanlines(region)) {
            const auto globalPos = region.getPosition() + pixel;
            image.setValue(globalPos, color);
        }
    }

    template <typename I> static Color minValue(I &image) {
        Color min = image.getValue({0, 0});
        for (auto pixel : AreaIterators::scanlines(image)) {
            auto pixelColor = image.getValue(pixel);
            if (pixelColor < min) {
                min = pixelColor;
            }
        }
        return min;
    }

    template <typename I> static Color maxValue(I &image) {
        Color max = image.getValue({0, 0});
        for (auto pixel : AreaIterators::scanlines(image)) {
            auto pixelColor = image.getValue(pixel);
            if (pixelColor > max) {
                max = pixelColor;
            }
        }
        return max;
    }

    template <typename I> static void fillWithRelativeGradient(I &source, I &target, const Gradient<Color> &gradient) {
        Color minValue = ImageAlgorithms::minValue(source);
        Color maxValue = ImageAlgorithms::maxValue(source);
        fillWithRelativeGradient(source, target, gradient, minValue, maxValue);
    }

    template <typename I>
    static void fillWithRelativeGradient(I &source, I &target, const Gradient<Color> &gradient, Color min, Color max) {
        const Color rangeEnd = max - min;
        for (auto pixel : AreaIterators::scanlines(source)) {
            auto pixelColor = source.getValue(pixel) - min;
            auto gradientPosition = (pixelColor / rangeEnd).clamp();
            auto gradientColor = gradient.interpolate(gradientPosition.r);
            target.setValue(pixel, gradientColor);
        }
    }

    template <typename I> static bool tileIsContainedInImage(const Tile &tile, I &image) {
        return tile.getPosition().x >= 0 && tile.getPosition().y >= 0 &&
               tile.getPosition().x + tile.getWidth() <= image.getWidth() &&
               tile.getPosition().y + tile.getHeight() <= image.getHeight();
    }
};

}
