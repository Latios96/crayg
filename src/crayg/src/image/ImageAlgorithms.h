#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_

#include "BucketImageBuffer.h"
#include "Image.h"
#include "ImageIterators.h"

namespace crayg {

class ImageAlgorithms {
  public:
    static void copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image);

    template <typename I> static void fill(I &image, const Color &color) {
        for (auto pixel : ImageIterators::lineByLine(image)) {
            image.setValue({pixel.x, pixel.y}, color);
        }
    }

    static bool bucketIsContainedInImage(const ImageBucket &bucket, Image &image);
};

}

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_
