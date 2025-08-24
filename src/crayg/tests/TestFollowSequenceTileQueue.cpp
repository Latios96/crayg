#include "crayg/foundation/areaiterators/tiles/tilequeues/FollowSequenceTileQueue.h"
#include "crayg/foundation/math/geometry/Tile.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("FollowSequenceTileQueue::nextTile") {

    std::vector<Tile> tiles(
        {{{0, 0}, 10, 10}, {{0, 10}, 10, 10}, {{0, 20}, 10, 10}, {{0, 30}, 10, 10}, {{0, 40}, 10, 10}});
    FollowSequenceTileQueue followSequenceTileQueue(tiles);

    SECTION("should return tiles in correct order ") {
        std::vector<int> yCoordinates;
        for (int i = 0; i < tiles.size(); i++) {
            const auto nextTile = *followSequenceTileQueue.nextTile();
            yCoordinates.push_back(nextTile.getPosition().y);
        }

        REQUIRE(yCoordinates == std::vector<int>({0, 10, 20, 30, 40}));
    }

    SECTION("should not delete tiles before destruction") {
        for (int i = 0; i < tiles.size(); i++) {
            followSequenceTileQueue.nextTile();
        }

        REQUIRE(tiles.size() == 5);
    }

    SECTION("should return empty optional if all tiles are consumed") {
        for (int i = 0; i < tiles.size(); i++) {
            followSequenceTileQueue.nextTile();
        }
        const auto emptyTile = followSequenceTileQueue.nextTile();

        REQUIRE(!emptyTile.has_value());
    }
}

TEST_CASE("FollowSequenceTileQueue::destruction") {
    std::vector<Tile> tiles(
        {{{0, 0}, 10, 10}, {{0, 10}, 10, 10}, {{0, 20}, 10, 10}, {{0, 30}, 10, 10}, {{0, 40}, 10, 10}});

    SECTION("should not remove any tiles if no tiles were consumed") {
        { FollowSequenceTileQueue followSequenceTileQueue(tiles); }
        REQUIRE(tiles.size() == 5);
    }
    SECTION("should remove all tiles if all tiles were consumed") {
        {
            FollowSequenceTileQueue followSequenceTileQueue(tiles);
            for (int i = 0; i < tiles.size(); i++) {
                followSequenceTileQueue.nextTile();
            }
        }
        REQUIRE(tiles.empty());
    }
    SECTION("should remove some consumed tiles") {
        {
            FollowSequenceTileQueue followSequenceTileQueue(tiles);
            followSequenceTileQueue.nextTile();
            followSequenceTileQueue.nextTile();
        }
        REQUIRE(tiles.size() == 3);
    }
}

}