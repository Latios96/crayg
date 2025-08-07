#include "crayg/foundation/areaiterators/buckets/BucketSequenceType.h"
#include "crayg/foundation/areaiterators/buckets/ImageBucketSequences.h"
#include "image/Image.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ImageBucketSequences::getSequence") {

    Image image(20, 10);

    SECTION("should get line by line sequence") {
        auto buckets = ImageBucketSequences::getSequence(image, 5, BucketSequenceType::LINE_BY_LINE);

        REQUIRE(buckets[0].getPosition() == Vector2i(0, 0));
    }

    SECTION("should get spiral sequence") {
        auto buckets = ImageBucketSequences::getSequence(image, 5, BucketSequenceType::SPIRAL);

        REQUIRE(buckets[0].getPosition() == Vector2i(10, 0));
    }
}

}