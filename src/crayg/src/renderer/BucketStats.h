#pragma once

#include "image/BucketImageBuffer.h"
#include "outputdrivers/OutputDriver.h"
#include <chrono>
#include <tbb/concurrent_vector.h>
#include <utils/DtoUtils.h>

namespace crayg {

CRAYG_DTO_2(ImageBucketTime, ImageBucket, imageBucket, float, seconds);

class BucketStats {
  public:
    void processBucketTime(BucketImageBuffer &bucketImageBuffer,
                           const std::chrono::steady_clock::time_point &startTime);
    void processBucketTimes(OutputDriver &outputDriver, const Resolution &resolution);

  private:
    tbb::concurrent_vector<ImageBucketTime> imageBucketTimes;
};

} // crayg
