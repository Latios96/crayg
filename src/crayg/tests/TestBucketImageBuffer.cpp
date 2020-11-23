//
// Created by Jan on 29.10.2020.
//
#include <image/BucketImageBuffer.h>
#include "catch2/catch.hpp"

namespace crayg {

struct ImageWrapper {
    Image image;
};

TEST_CASE("BucketImageBuffer") {

    SECTION("shouldConstructCorrectly") {
        BucketImageBuffer bucketImageBuffer(0, 1, 20, 30);

        REQUIRE(bucketImageBuffer.imageBucket.getX() == 0);
        REQUIRE(bucketImageBuffer.imageBucket.getY() == 1);
        REQUIRE(bucketImageBuffer.imageBucket.getWidth() == 20);
        REQUIRE(bucketImageBuffer.imageBucket.getHeight() == 30);
        REQUIRE(bucketImageBuffer.image.getWidth() == 20);
        REQUIRE(bucketImageBuffer.image.getHeight() == 30);
    }
}

}

