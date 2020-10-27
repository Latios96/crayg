//
// Created by Jan on 21.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_

#include "Image.h"
#include "ImageBucket.h"
#include <vector>

class ImageBucketSequences {
 public:
    static std::vector<ImageBucket> lineByLine(const Image &image, int bucketWidth);
};

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEBUCKETSEQUENCES_H_
