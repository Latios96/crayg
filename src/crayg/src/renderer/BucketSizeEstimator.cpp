#include "BucketSizeEstimator.h"
#include "Logger.h"
#include <thread>

namespace crayg {
int BucketSizeEstimator::estimateBucketSize() const {
    return estimateBucketSize(std::thread::hardware_concurrency());
}

int BucketSizeEstimator::estimateBucketSize(int threadCount) const {
    const int pixelCount = renderSettings.resolution.getWidth() * renderSettings.resolution.getHeight();
    const int estimatedBucketSize =
        static_cast<int>(std::sqrt(pixelCount / threadCount)) / BucketSizeEstimator::BUCKETS_PER_THREAD;
    const int bucketSize =
        std::clamp(estimatedBucketSize, BucketSizeEstimator::MIN_BUCKET_SIZE, BucketSizeEstimator::MAX_BUCKET_SIZE);
    Logger::info("Choosing a bucket size of {0}x{0} pixels", bucketSize);
    return bucketSize;
}

BucketSizeEstimator::BucketSizeEstimator(const RenderSettings &renderSettings) : renderSettings(renderSettings) {
}
} // crayg