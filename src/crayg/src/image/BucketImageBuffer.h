#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_BUCKETIMAGEBUFFER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_BUCKETIMAGEBUFFER_H_

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

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_BUCKETIMAGEBUFFER_H_
