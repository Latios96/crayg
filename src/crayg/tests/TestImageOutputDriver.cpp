//
// Created by Jan on 29.10.2020.
//

#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/ImageOutputDriver.h>
#include <image/ImageAlgorithms.h>

TEST_CASE("ImageOutputDriver") {
    Image image(200, 200);
    ImageOutputDriver imageOutputDriver(image);

    SECTION("shouldWriteBucket") {
        BucketImageBuffer bucketImageBuffer(0,0,30,30);
        ImageAlgorithms::fill(bucketImageBuffer.image, Color::createWhite());

        imageOutputDriver.prepareBucket(bucketImageBuffer.imageBucket);
        imageOutputDriver.writeBucketImageBuffer(bucketImageBuffer);

        REQUIRE(image.getValue(10,10) == Color::createWhite());
    }

}