//
// Created by Jan on 29.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_

#include "Image.h"
#include "BucketImageBuffer.h"
class ImageAlgorithms {
 public:
    static void copyBucketImageBufferIntoImage(const BucketImageBuffer &bucketImageBuffer, Image &image);
    static bool bucketIsContainedInImage(const ImageBucket &bucket, Image &image);
};

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEALGORITHMS_H_
