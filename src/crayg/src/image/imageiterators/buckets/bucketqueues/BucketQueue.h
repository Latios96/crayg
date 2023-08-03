#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETQUEUES_BUCKETQUEUE_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETQUEUES_BUCKETQUEUE_H_

#include "BucketQueueMode.h"
#include "FollowMouseBucketQueue.h"
#include "FollowSequenceBucketQueue.h"
#include "image/ImageBucket.h"
#include <mutex>
#include <optional>
#include <vector>

namespace crayg {

struct BucketQueue {
    enum Mode { FOLLOW_SEQUENCE, FOLLOW_MOUSE };

    explicit BucketQueue(const std::function<Vector2i()> &getMousePosition);
    void start(std::vector<ImageBucket> &buckets);
    std::optional<ImageBucket> nextBucket();
    Mode getCurrentMode() const;
    void switchMode();

  private:
    Mode currentMode;
    std::unique_ptr<BucketQueueMode> modeDelegate;

    std::vector<ImageBucket> *buckets = nullptr;
    const std::function<Vector2i()> &getMousePosition;

    std::mutex delegateMutex;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETQUEUES_BUCKETQUEUE_H_
