#include "FollowSequenceBucketQueue.h"

namespace crayg {
FollowSequenceBucketQueue::FollowSequenceBucketQueue(std::vector<ImageBucket> &buckets) : BucketQueueMode(buckets) {
}

std::optional<ImageBucket> FollowSequenceBucketQueue::nextBucket() {
    if (lastBucketIndex >= static_cast<int>(buckets.size()) - 1) {
        return std::nullopt;
    }
    lastBucketIndex++;
    return buckets[lastBucketIndex];
}

FollowSequenceBucketQueue::~FollowSequenceBucketQueue() {
    if (buckets.empty()) {
        return;
    }
    if (lastBucketIndex < 0) {
        return;
    }
    buckets.erase(buckets.begin(), buckets.begin() + lastBucketIndex + 1);
}

}