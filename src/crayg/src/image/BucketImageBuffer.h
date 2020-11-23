//
// Created by Jan on 29.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_BUCKETIMAGEBUFFER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_BUCKETIMAGEBUFFER_H_

#include "ImageBucket.h"
#include "Image.h"

namespace crayg {

struct BucketImageBuffer {
 public:
    ImageBucket imageBucket;
    Image image;
    BucketImageBuffer(int x, int y, int width, int height);
    BucketImageBuffer(const ImageBucket &imageBucket);
};

}

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_BUCKETIMAGEBUFFER_H_
