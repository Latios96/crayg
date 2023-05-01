#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_

#include "BucketImageBuffer.h"
#include "Image.h"
#include "basics/Gradient.h"
#include "imageiterators/pixels/ImageIterators.h"

namespace crayg {

class ImageAlgorithms {
  public:
    static void copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image);

    template <typename I> static void fill(I &image, const Color &color) {
        for (auto pixel : ImageIterators::lineByLine(image)) {
            image.setValue(pixel, color);
        }
    }

    template <typename I> static Color minValue(I &image) {
        Color min = image.getValue({0, 0});
        for (auto pixel : ImageIterators::lineByLine(image)) {
            auto pixelColor = image.getValue(pixel);
            if (pixelColor < min) {
                min = pixelColor;
            }
        }
        return min;
    }

    template <typename I> static Color maxValue(I &image) {
        Color max = image.getValue({0, 0});
        for (auto pixel : ImageIterators::lineByLine(image)) {
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
        for (auto pixel : ImageIterators::lineByLine(source)) {
            auto pixelColor = source.getValue(pixel) - min;
            auto gradientPosition = pixelColor / rangeEnd;
            auto gradientColor = gradient.interpolate(gradientPosition.r);
            target.setValue(pixel, gradientColor);
        }
    }

    static bool bucketIsContainedInImage(const ImageBucket &bucket, Image &image);
};

}

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_
