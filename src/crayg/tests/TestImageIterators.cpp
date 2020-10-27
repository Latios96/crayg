#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/ImageIterators.h>
#include <iostream>
#include <image/ImageBucketSequences.h>

TEST_CASE("ImageIterators", "[ImageIterators]") {

    std::vector<PixelPosition> positions;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            positions.emplace_back(x, y);
        }
    }

    SECTION("testLineByLineWithImage") {
        Image image(5, 5);

        int counter = 0;
        for (auto pixel : ImageIterators::lineByLine(image)) {
            REQUIRE(pixel.x == positions[counter].x);
            REQUIRE(pixel.y == positions[counter].y);
            counter++;
        }
        REQUIRE(counter == 24);
    }

    SECTION("testLineByLineWithBucket") {
        ImageBucket bucket(0, 0, 5, 5);

        int counter = 0;
        for (auto pixel : ImageIterators::lineByLine(bucket)) {
            REQUIRE(pixel.x == positions[counter].x);
            REQUIRE(pixel.y == positions[counter].y);
            counter++;
        }
        REQUIRE(counter == 24);

    }

}