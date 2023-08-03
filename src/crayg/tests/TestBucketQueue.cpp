#include "image/imageiterators/buckets/ImageBucketSequences.h"
#include "image/imageiterators/buckets/bucketqueues/BucketQueue.h"
#include <catch2/catch.hpp>
#include <tbb/task_group.h>

namespace crayg {
// constructing should default to FOLLOW_SEQUENCE
// should return buckets thread safe
TEST_CASE("TestBucketQueue::construct") {

    std::vector<ImageBucket> buckets(
        {{{0, 0}, 10, 10}, {{0, 10}, 10, 10}, {{0, 20}, 10, 10}, {{0, 30}, 10, 10}, {{0, 40}, 10, 10}});

    SECTION("should default to FOLLOW_SEQUENCE ") {
        BucketQueue bucketQueue([]() { return Vector2i(); });
        bucketQueue.start(buckets);

        REQUIRE(bucketQueue.getCurrentMode() == BucketQueue::Mode::FOLLOW_SEQUENCE);
    }
}

TEST_CASE("TestBucketQueue::nextBucket") {
    SECTION("should return buckets thread safe") {
        std::vector<ImageBucket> bucketSequence =
            ImageBucketSequences::getSequence(Resolution(1920, 1080), 8, BucketSequenceType::SPIRAL);
        BucketQueue bucketQueue([]() { return Vector2i(); });
        bucketQueue.start(bucketSequence);

        tbb::task_group task_group;
        for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++) {
            task_group.run([&bucketQueue]() {
                while (true) {
                    const auto imageBucket = bucketQueue.nextBucket();
                    if (!imageBucket) {
                        return;
                    }
                }
            });
        }
        task_group.wait();
    }
}

}