#pragma once

#include "scene/RenderSettings.h"

namespace crayg {

class BucketSizeEstimator {
  public:
    explicit BucketSizeEstimator(const RenderSettings &renderSettings);
    int estimateBucketSize() const;
    int estimateBucketSize(int threadCount) const;

  private:
    const RenderSettings &renderSettings;
    static constexpr int MIN_BUCKET_SIZE = 8;
    static constexpr int MAX_BUCKET_SIZE = 64;
    static constexpr int BUCKETS_PER_THREAD = 4;
};

} // crayg
