#pragma once

#include "Image.h"
#include "ImageBucket.h"

namespace crayg {

struct BucketImageBuffer {
  public:
    ImageBucket imageBucket;
    Image image;
    BucketImageBuffer();
    BucketImageBuffer(const Vector2i &position, int width, int height);
    BucketImageBuffer(const ImageBucket &imageBucket);
};

}
