#include "crayg/foundation/areaiterators/tiles/TileSequences.h"
#include "crayg/foundation/areaiterators/tiles/tilequeues/TileQueue.h"
#include <catch2/catch.hpp>
#include <tbb/task_group.h>
#include <thread>

namespace crayg {

TEST_CASE("TestTileQueue::construct") {

    std::vector<Tile> tiles(
        {{{0, 0}, 10, 10}, {{0, 10}, 10, 10}, {{0, 20}, 10, 10}, {{0, 30}, 10, 10}, {{0, 40}, 10, 10}});

    SECTION("should default to FOLLOW_SEQUENCE ") {
        TileQueue tileQueue([]() { return Vector2i(); });
        tileQueue.start(tiles);

        REQUIRE(tileQueue.getCurrentMode() == TileQueue::TileFollowMode::FOLLOW_SEQUENCE);
    }
}

TEST_CASE("TestTileQueue::nextTile") {
    SECTION("should return tiles thread safe") {
        std::vector<Tile> tileSequence =
            TileSequences::getSequence(Resolution(1920, 1080), 8, TileSequenceType::SPIRAL);
        TileQueue tileQueue([]() { return Vector2i(); });
        tileQueue.start(tileSequence);

        tbb::task_group task_group;
        for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++) {
            task_group.run([&tileQueue]() {
                while (true) {
                    const auto tile = tileQueue.nextTile();
                    if (!tile) {
                        return;
                    }
                }
            });
        }
        task_group.wait();
    }
}

}