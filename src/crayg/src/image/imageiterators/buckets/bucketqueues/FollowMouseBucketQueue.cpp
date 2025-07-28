#include "FollowMouseBucketQueue.h"

namespace crayg {
FollowMouseBucketQueue::FollowMouseBucketQueue(std::vector<ImageBucket> &buckets,
                                               const std::function<Vector2i()> &getMousePosition)
    : BucketQueueMode(buckets), getMousePosition(getMousePosition) {
}

std::optional<ImageBucket> FollowMouseBucketQueue::nextBucket() {
    if (buckets.empty()) {
        return std::nullopt;
    }
    const auto mousePosition = getMousePosition();
    const int nearestBucketIndex = findNearestBucket(mousePosition);
    ImageBucket nearestBucket = buckets[nearestBucketIndex];
    buckets.erase(buckets.begin() + nearestBucketIndex);
    return nearestBucket;
}

float squaredDistanceBetween(const Vector2i &mousePosition, const ImageBucket &bucket) {
    const Vector2i bucketMiddle = bucket.getPosition() + Vector2i(bucket.getHeight() / 2, bucket.getWidth() / 2);
    return (bucketMiddle - mousePosition).lengthSquared();
}

int FollowMouseBucketQueue::findNearestBucket(const Vector2i &mousePosition) {
    float minDistance = std::numeric_limits<float>::max();
    int index = 0;
    for (int i = 0; i < buckets.size(); i++) {
        const float distance = squaredDistanceBetween(mousePosition, buckets[i]);
        if (distance < minDistance) {
            minDistance = distance;
            index = i;
        }
    }
    return index;
}

}