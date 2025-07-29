#pragma once

#include "image/BucketImageBuffer.h"
#include "outputdrivers/NextGenOutputDriver.h"
#include <chrono>
#include <tbb/concurrent_vector.h>
#include <utils/DtoUtils.h>

namespace crayg {

CRAYG_DTO_2(ImageBucketTime, ImageBucket, imageBucket, float, seconds);

class BucketStats {
  public:
    void processBucketTime(Film &film, const ImageBucket &imageBucket,
                           const std::chrono::steady_clock::time_point &startTime);
    void processBucketTimes(NextGenOutputDriver &outputDriver, const Resolution &resolution);

  private:
    tbb::concurrent_vector<ImageBucketTime> imageBucketTimes;
};

}
