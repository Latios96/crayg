#pragma once

#include "BucketQueueMode.h"

namespace crayg {

class FollowSequenceBucketQueue : public BucketQueueMode {
  public:
    explicit FollowSequenceBucketQueue(std::vector<ImageBucket> &buckets);
    std::optional<ImageBucket> nextBucket() override;
    ~FollowSequenceBucketQueue() override;

  private:
    int lastBucketIndex = -1;
};

} // crayg
