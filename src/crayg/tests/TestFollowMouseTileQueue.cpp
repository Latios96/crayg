#include "basics/Resolution.h"
#include "crayg/foundation/areaiterators/tiles/TileSequences.h"
#include "crayg/foundation/areaiterators/tiles/tilequeues/FollowMouseTileQueue.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("FollowMouseTileQueue::nextTile") {

    Vector2i mousePosition;
    auto tiles = TileSequences::getSequence(Resolution(48, 24), 8, TileSequenceType::SPIRAL);
    FollowMouseTileQueue followMouseTileQueue(tiles, [&mousePosition]() { return mousePosition; });

    SECTION("should select nearest tile from fresh sequence") {
        mousePosition = {48, 0};

        const auto tile = followMouseTileQueue.nextTile();

        REQUIRE(tile->getPosition() == Vector2i(40, 0));
        REQUIRE(tiles.size() == 23);
    }

    SECTION("should select nearest tile from fresh sequence with one tile taken") {
        mousePosition = {48, 0};
        followMouseTileQueue.nextTile();

        const auto tile = followMouseTileQueue.nextTile();

        REQUIRE(tile->getPosition() == Vector2i(40, 4));
        REQUIRE(tiles.size() == 22);
    }

    SECTION("should select nearest tile from fresh sequence with tiles taken") {
        mousePosition = {48, 0};
        followMouseTileQueue.nextTile();
        followMouseTileQueue.nextTile();
        mousePosition = {0, 0};
        followMouseTileQueue.nextTile();
        followMouseTileQueue.nextTile();

        const auto tile = followMouseTileQueue.nextTile();

        REQUIRE(tile->getPosition() == Vector2i(8, 0));
        REQUIRE(tiles.size() == 19);
    }

    SECTION("should select nearest tile for mouse position outside image") {
        mousePosition = {100, -25};

        const auto tile = followMouseTileQueue.nextTile();

        REQUIRE(tile->getPosition() == Vector2i(40, 0));
        REQUIRE(tiles.size() == 23);
    }

    SECTION("should return empty optional if all tiles were consumed") {
        std::vector<Tile> tiles;
        FollowMouseTileQueue followMouseTileQueue(tiles, [&mousePosition]() { return mousePosition; });

        const auto tile = followMouseTileQueue.nextTile();

        REQUIRE(!tile.has_value());
    }
}

}