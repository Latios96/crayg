#pragma once

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
