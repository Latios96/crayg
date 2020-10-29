//
// Created by Jan on 29.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_

#include "Image.h"
#include "ImageIterators.h"
#include "BucketImageBuffer.h"

class ImageAlgorithms {
 public:
    static void copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image);

    static void fill(Image &image, const Color &color) {
        for (auto pixel : ImageIterators::lineByLine(image)) {
            image.setValue(pixel.x, pixel.y, color);
        }
    }
    static bool bucketIsContainedInImage(const ImageBucket &bucket, Image &image);
};

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_
