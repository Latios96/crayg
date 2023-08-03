#include "basics/Resolution.h"
#include "image/imageiterators/buckets/ImageBucketSequences.h"
#include "image/imageiterators/buckets/bucketqueues/FollowMouseBucketQueue.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("FollowMouseBucketQueue::nextBucket") {

    Vector2i mousePosition;
    auto buckets = ImageBucketSequences::getSequence(Resolution(48, 24), 8, BucketSequenceType::SPIRAL);
    FollowMouseBucketQueue followMouseBucketQueue(buckets, [&mousePosition]() { return mousePosition; });

    SECTION("should select nearest bucket from fresh sequence") {
        mousePosition = {48, 0};

        const auto bucket = followMouseBucketQueue.nextBucket();

        REQUIRE(bucket->getPosition() == Vector2i(40, 0));
        REQUIRE(buckets.size() == 23);
    }

    SECTION("should select nearest bucket from fresh sequence with one bucket taken") {
        mousePosition = {48, 0};
        followMouseBucketQueue.nextBucket();

        const auto bucket = followMouseBucketQueue.nextBucket();

        REQUIRE(bucket->getPosition() == Vector2i(40, 4));
        REQUIRE(buckets.size() == 22);
    }

    SECTION("should select nearest bucket from fresh sequence with buckets taken") {
        mousePosition = {48, 0};
        followMouseBucketQueue.nextBucket();
        followMouseBucketQueue.nextBucket();
        mousePosition = {0, 0};
        followMouseBucketQueue.nextBucket();
        followMouseBucketQueue.nextBucket();

        const auto bucket = followMouseBucketQueue.nextBucket();

        REQUIRE(bucket->getPosition() == Vector2i(8, 0));
        REQUIRE(buckets.size() == 19);
    }

    SECTION("should select nearest bucket for mouse position outside image") {
        mousePosition = {100, -25};

        const auto bucket = followMouseBucketQueue.nextBucket();

        REQUIRE(bucket->getPosition() == Vector2i(40, 0));
        REQUIRE(buckets.size() == 23);
    }

    SECTION("should return empty optional if all buckets were consumed") {
        std::vector<ImageBucket> buckets;
        FollowMouseBucketQueue followMouseBucketQueue(buckets, [&mousePosition]() { return mousePosition; });

        const auto bucket = followMouseBucketQueue.nextBucket();

        REQUIRE(!bucket.has_value());
    }
}

}