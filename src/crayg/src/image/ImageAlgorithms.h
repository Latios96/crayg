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

    static bool bucketIsContainedInImage(const ImageBucket &bucket, Image &image);
};

}

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_
