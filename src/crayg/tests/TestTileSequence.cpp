#include "crayg/foundation/areaiterators/tiles/TileSequenceType.h"
#include "crayg/foundation/areaiterators/tiles/TileSequences.h"
#include "crayg/image/Image.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ImageTileSequences::getSequence") {

    Image image(20, 10);

    SECTION("should get line by line sequence") {
        auto tiles = TileSequences::getSequence(image, 5, TileSequenceType::SCANLINE);

        REQUIRE(tiles[0].getPosition() == Vector2i(0, 0));
    }

    SECTION("should get spiral sequence") {
        auto tiles = TileSequences::getSequence(image, 5, TileSequenceType::SPIRAL);

        REQUIRE(tiles[0].getPosition() == Vector2i(10, 0));
    }
}

}