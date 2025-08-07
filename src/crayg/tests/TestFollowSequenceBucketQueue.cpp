#include "crayg/foundation/areaiterators/buckets/bucketqueues/FollowSequenceBucketQueue.h"
#include "image/ImageBucket.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("FollowSequenceBucketQueue::nextBucket") {

    std::vector<ImageBucket> buckets(
        {{{0, 0}, 10, 10}, {{0, 10}, 10, 10}, {{0, 20}, 10, 10}, {{0, 30}, 10, 10}, {{0, 40}, 10, 10}});
    FollowSequenceBucketQueue followSequenceBucketQueue(buckets);

    SECTION("should return buckets in correct order ") {
        std::vector<int> yCoordinates;
        for (int i = 0; i < buckets.size(); i++) {
            const auto nextBucket = *followSequenceBucketQueue.nextBucket();
            yCoordinates.push_back(nextBucket.getPosition().y);
        }

        REQUIRE(yCoordinates == std::vector<int>({0, 10, 20, 30, 40}));
    }

    SECTION("should not delete buckets before destruction") {
        for (int i = 0; i < buckets.size(); i++) {
            followSequenceBucketQueue.nextBucket();
        }

        REQUIRE(buckets.size() == 5);
    }

    SECTION("should return empty optional if all buckets are consumed") {
        for (int i = 0; i < buckets.size(); i++) {
            followSequenceBucketQueue.nextBucket();
        }
        const auto emptyBucket = followSequenceBucketQueue.nextBucket();

        REQUIRE(!emptyBucket.has_value());
    }
}

TEST_CASE("FollowSequenceBucketQueue::destruction") {
    std::vector<ImageBucket> buckets(
        {{{0, 0}, 10, 10}, {{0, 10}, 10, 10}, {{0, 20}, 10, 10}, {{0, 30}, 10, 10}, {{0, 40}, 10, 10}});

    SECTION("should not remove any buckets if no buckets were consumed") {
        { FollowSequenceBucketQueue followSequenceBucketQueue(buckets); }
        REQUIRE(buckets.size() == 5);
    }
    SECTION("should remove all buckets if all buckets were consumed") {
        {
            FollowSequenceBucketQueue followSequenceBucketQueue(buckets);
            for (int i = 0; i < buckets.size(); i++) {
                followSequenceBucketQueue.nextBucket();
            }
        }
        REQUIRE(buckets.empty());
    }
    SECTION("should remove some consumed buckets") {
        {
            FollowSequenceBucketQueue followSequenceBucketQueue(buckets);
            followSequenceBucketQueue.nextBucket();
            followSequenceBucketQueue.nextBucket();
        }
        REQUIRE(buckets.size() == 3);
    }
}

}