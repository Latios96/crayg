#include "BucketQueue.h"

namespace crayg {

BucketQueue::BucketQueue(std::vector<ImageBucket> &buckets) : buckets(buckets) {
    currentMode = FOLLOW_SEQUENCE;
    modeDelegate = std::make_unique<FollowSequenceBucketQueue>(buckets);
}

std::optional<ImageBucket> BucketQueue::nextBucket() {
    std::lock_guard<std::mutex> lock(delegateMutex);
    return modeDelegate->nextBucket();
}

BucketQueue::Mode BucketQueue::getCurrentMode() const {
    return currentMode;
}

} // crayg