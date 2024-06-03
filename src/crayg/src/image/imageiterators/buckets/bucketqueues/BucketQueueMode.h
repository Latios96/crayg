#pragma once

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
