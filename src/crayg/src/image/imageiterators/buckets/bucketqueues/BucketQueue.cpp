#include "BucketQueue.h"
#include "Logger.h"

namespace crayg {

BucketQueue::BucketQueue(const std::function<Vector2i()> &getMousePosition) : getMousePosition(getMousePosition) {
    currentMode = FOLLOW_SEQUENCE;
}

void BucketQueue::start(std::vector<ImageBucket> &buckets) {
    this->buckets = &buckets;
    currentMode = FOLLOW_SEQUENCE;
    modeDelegate = std::make_unique<FollowSequenceBucketQueue>(buckets);
}

std::optional<ImageBucket> BucketQueue::nextBucket() {
    std::lock_guard<std::mutex> lock(delegateMutex);
    return modeDelegate->nextBucket();
}

void BucketQueue::switchMode() {
    std::lock_guard<std::mutex> lock(delegateMutex);
    switch (currentMode) {
    case FOLLOW_MOUSE:
        currentMode = FOLLOW_SEQUENCE;
        modeDelegate = std::make_unique<FollowSequenceBucketQueue>(*buckets);
        break;
    case FOLLOW_SEQUENCE:
        currentMode = FOLLOW_MOUSE;
        modeDelegate = std::make_unique<FollowMouseBucketQueue>(*buckets, getMousePosition);
        break;
    }
}

BucketQueue::Mode BucketQueue::getCurrentMode() const {
    return currentMode;
}

} // crayg