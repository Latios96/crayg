#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_OUTPUTDRIVER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_OUTPUTDRIVER_H_

#include "BucketImageBuffer.h"

namespace crayg {

class OutputDriver {
 public:
    virtual void prepareBucket(const ImageBucket &imageBucket) = 0;
    virtual void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) = 0;
    virtual ~OutputDriver() = default;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_OUTPUTDRIVER_H_
