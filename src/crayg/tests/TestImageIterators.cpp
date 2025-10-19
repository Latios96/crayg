#include "crayg/foundation/areaiterators/AreaIterators.h"
#include "crayg/foundation/areaiterators/tiles/TileSequences.h"
#include "crayg/image/Image.h"
#include <catch2/catch.hpp>
#include <iostream>

namespace crayg {

TEST_CASE("ImageIterators", "[ImageIterators]") {

    std::vector<Vector2i> positions;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            positions.emplace_back(x, y);
        }
    }

    SECTION("testScanlineWithImage") {
        Image image(5, 5);
        std::vector<Vector2i> visitedPositions;

        for (auto pixel : AreaIterators::scanlines(image)) {
            visitedPositions.push_back(pixel);
        }
        REQUIRE(visitedPositions == positions);
    }

    SECTION("testScanlineWithTile") {
        Tile tile({0, 0}, 5, 5);
        std::vector<Vector2i> visitedPositions;

        for (auto pixel : AreaIterators::scanlines(tile)) {
            visitedPositions.push_back(pixel);
        }
        REQUIRE(visitedPositions == positions);
    }
}

}