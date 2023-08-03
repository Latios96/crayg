#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETQUEUES_FOLLOWMOUSEBUCKETQUEUE_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETQUEUES_FOLLOWMOUSEBUCKETQUEUE_H_

#include "BucketQueueMode.h"
#include <functional>

namespace crayg {

class FollowMouseBucketQueue : public BucketQueueMode {
  public:
    explicit FollowMouseBucketQueue(std::vector<ImageBucket> &buckets,
                                    const std::function<Vector2i()> &getMousePosition);
    std::optional<ImageBucket> nextBucket() override;
    ~FollowMouseBucketQueue() override = default;

  private:
    int findNearestBucket(const Vector2i &mousePosition);
    const std::function<Vector2i()> getMousePosition;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETQUEUES_FOLLOWMOUSEBUCKETQUEUE_H_
