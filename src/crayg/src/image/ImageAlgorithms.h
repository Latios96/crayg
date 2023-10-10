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
    static void copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image,
                                               const std::vector<std::string> &channelsToUpdate);
    static void updateChannel(Image &image, const std::string &channelName, PixelBuffer *pixelBuffer);

    template <typename I> static void fill(I &image, const Color &color) {
        for (auto pixel : ImageIterators::lineByLine(image)) {
            image.setValue(pixel, color);
        }
    }

    template <typename I> static void fill(I &image, const Color &color, const ImageBucket &region) {
        const bool isContained = bucketIsContainedInImage(region, image);

        if (!isContained) {
            return;
        }

        for (auto pixel : ImageIterators::lineByLine(region)) {
            const auto globalPos = region.getPosition() + pixel;
            image.setValue(globalPos, color);
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
            auto gradientPosition = (pixelColor / rangeEnd).clamp();
            auto gradientColor = gradient.interpolate(gradientPosition.r);
            target.setValue(pixel, gradientColor);
        }
    }

    template <typename I> static bool bucketIsContainedInImage(const ImageBucket &bucket, I &image) {
        return bucket.getPosition().x >= 0 && bucket.getPosition().y >= 0 &&
               bucket.getPosition().x + bucket.getWidth() <= image.getWidth() &&
               bucket.getPosition().y + bucket.getHeight() <= image.getHeight();
    }
};

}

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_
