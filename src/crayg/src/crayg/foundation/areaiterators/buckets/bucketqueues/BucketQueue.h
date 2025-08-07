#pragma once

#include "BucketQueueMode.h"
#include "FollowMouseBucketQueue.h"
#include "FollowSequenceBucketQueue.h"
#include "image/ImageBucket.h"
#include <mutex>
#include <optional>
#include <vector>

namespace crayg {

struct BucketQueue {
    enum class BucketFollowMode { FOLLOW_SEQUENCE, FOLLOW_MOUSE };

    explicit BucketQueue(const std::function<Vector2i()> &getMousePosition);
    void start(std::vector<ImageBucket> &buckets);
    std::optional<ImageBucket> nextBucket();
    BucketFollowMode getCurrentMode() const;
    void switchMode();

  private:
    BucketFollowMode currentMode;
    std::unique_ptr<BucketQueueMode> modeDelegate;

    std::vector<ImageBucket> *buckets = nullptr;
    const std::function<Vector2i()> &getMousePosition;

    std::mutex delegateMutex;
};

}
