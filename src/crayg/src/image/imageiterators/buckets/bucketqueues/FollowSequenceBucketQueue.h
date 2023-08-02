#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETQUEUES_FOLLOWSEQUENCEBUCKETQUEUE_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETQUEUES_FOLLOWSEQUENCEBUCKETQUEUE_H_

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

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETQUEUES_FOLLOWSEQUENCEBUCKETQUEUE_H_
