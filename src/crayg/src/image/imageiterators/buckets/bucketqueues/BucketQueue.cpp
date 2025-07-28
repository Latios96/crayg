#include "BucketQueue.h"
#include "Logger.h"

namespace crayg {

BucketQueue::BucketQueue(const std::function<Vector2i()> &getMousePosition) : getMousePosition(getMousePosition) {
    currentMode = BucketFollowMode::FOLLOW_SEQUENCE;
}

void BucketQueue::start(std::vector<ImageBucket> &buckets) {
    this->buckets = &buckets;
    currentMode = BucketFollowMode::FOLLOW_SEQUENCE;
    modeDelegate = std::make_unique<FollowSequenceBucketQueue>(buckets);
}

std::optional<ImageBucket> BucketQueue::nextBucket() {
    std::lock_guard<std::mutex> lock(delegateMutex);
    return modeDelegate->nextBucket();
}

void BucketQueue::switchMode() {
    std::lock_guard<std::mutex> lock(delegateMutex);
    switch (currentMode) {
    case BucketFollowMode::FOLLOW_MOUSE:
        currentMode = BucketFollowMode::FOLLOW_SEQUENCE;
        modeDelegate = std::make_unique<FollowSequenceBucketQueue>(*buckets);
        break;
    case BucketFollowMode::FOLLOW_SEQUENCE:
        currentMode = BucketFollowMode::FOLLOW_MOUSE;
        modeDelegate = std::make_unique<FollowMouseBucketQueue>(*buckets, getMousePosition);
        break;
    }
}

BucketQueue::BucketFollowMode BucketQueue::getCurrentMode() const {
    return currentMode;
}

}