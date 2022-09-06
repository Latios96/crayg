#include <catch2/catch.hpp>
#include "renderer/BucketSizeEstimator.h"

namespace crayg {

TEST_CASE("BucketSizeEstimator::estimateBucketSize") {
    const int threadCount = 32;

    SECTION("should estimate less buckets than thread count") {
        const auto testData = GENERATE(table<Resolution, int>({{{200, 200}, 8},
                                                               {{500, 500}, 22},
                                                               {{700, 700}, 30},
                                                               {{800, 800}, 35},
                                                               {{2000, 2000}, 64},
                                                               {{8000, 8000}, 64}}));
        RenderSettings renderSettings;
        renderSettings.resolution = std::get<0>(testData);
        const int expectedBucketSize = std::get<1>(testData);
        const BucketSizeEstimator bucketSizeEstimator(renderSettings);

        const int estimatedBucketSize = bucketSizeEstimator.estimateBucketSize(threadCount);

        REQUIRE(estimatedBucketSize == expectedBucketSize);
    }
}

}