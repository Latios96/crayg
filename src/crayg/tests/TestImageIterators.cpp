#include "crayg/foundation/areaiterators/AreaIterators.h"
#include <catch2/catch.hpp>
#include <crayg/foundation/areaiterators/buckets/ImageBucketSequences.h>
#include <image/Image.h>
#include <iostream>

namespace crayg {

TEST_CASE("ImageIterators", "[ImageIterators]") {

    std::vector<Vector2i> positions;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            positions.emplace_back(x, y);
        }
    }

    SECTION("testLineByLineWithImage") {
        Image image(5, 5);
        std::vector<Vector2i> visitedPositions;

        for (auto pixel : AreaIterators::lineByLine(image)) {
            visitedPositions.push_back(pixel);
        }
        REQUIRE(visitedPositions == positions);
    }

    SECTION("testLineByLineWithBucket") {
        ImageBucket bucket({0, 0}, 5, 5);
        std::vector<Vector2i> visitedPositions;

        for (auto pixel : AreaIterators::lineByLine(bucket)) {
            visitedPositions.push_back(pixel);
        }
        REQUIRE(visitedPositions == positions);
    }
}

}