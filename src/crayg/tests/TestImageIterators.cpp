#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/ImageIterators.h>
#include <iostream>
#include <image/ImageBucketSequences.h>

namespace crayg {

TEST_CASE("ImageIterators", "[ImageIterators]") {

    std::vector<PixelPosition> positions;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            positions.emplace_back(x, y);
        }
    }

    SECTION("testLineByLineWithImage") {
        Image image(5, 5);
        std::vector<PixelPosition> visitedPositions;

        for (auto pixel : ImageIterators::lineByLine(image)) {
            visitedPositions.push_back(pixel);
        }
        REQUIRE(visitedPositions == positions);
    }

    SECTION("testLineByLineWithBucket") {
        ImageBucket bucket(0, 0, 5, 5);
        std::vector<PixelPosition> visitedPositions;

        for (auto pixel : ImageIterators::lineByLine(bucket)) {
            visitedPositions.push_back(pixel);
        }
        REQUIRE(visitedPositions == positions);

    }
}

}