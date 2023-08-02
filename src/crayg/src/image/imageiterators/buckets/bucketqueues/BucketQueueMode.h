#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETS_BUCKETQUEUE_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETS_BUCKETQUEUE_H_

#include "image/ImageBucket.h"
#include <optional>
#include <vector>

namespace crayg {

struct BucketQueueMode {
    explicit BucketQueueMode(std::vector<ImageBucket> &buckets) : buckets(buckets) {
    }

    virtual std::optional<ImageBucket> nextBucket() = 0;

    virtual ~BucketQueueMode() = default;

  protected:
    std::vector<ImageBucket> &buckets;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETS_BUCKETQUEUE_H_
