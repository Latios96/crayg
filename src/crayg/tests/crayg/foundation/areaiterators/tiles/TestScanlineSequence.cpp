#include "crayg/foundation/areaiterators/tiles/ScanlineSequence.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ScanlineSequence::getTiles") {

    SECTION("testScanlineSequenceWorksCorrectly") {
        ScanlineSequence scanlineSequence({20, 10}, 2);

        const std::vector<Tile> tiles = scanlineSequence.getTiles();

        REQUIRE(tiles ==
                std::vector<Tile>({Tile({0, 0}, 2, 2),  Tile({2, 0}, 2, 2),  Tile({4, 0}, 2, 2),  Tile({6, 0}, 2, 2),
                                   Tile({8, 0}, 2, 2),  Tile({10, 0}, 2, 2), Tile({12, 0}, 2, 2), Tile({14, 0}, 2, 2),
                                   Tile({16, 0}, 2, 2), Tile({18, 0}, 2, 2),

                                   Tile({0, 2}, 2, 2),  Tile({2, 2}, 2, 2),  Tile({4, 2}, 2, 2),  Tile({6, 2}, 2, 2),
                                   Tile({8, 2}, 2, 2),  Tile({10, 2}, 2, 2), Tile({12, 2}, 2, 2), Tile({14, 2}, 2, 2),
                                   Tile({16, 2}, 2, 2), Tile({18, 2}, 2, 2),

                                   Tile({0, 4}, 2, 2),  Tile({2, 4}, 2, 2),  Tile({4, 4}, 2, 2),  Tile({6, 4}, 2, 2),
                                   Tile({8, 4}, 2, 2),  Tile({10, 4}, 2, 2), Tile({12, 4}, 2, 2), Tile({14, 4}, 2, 2),
                                   Tile({16, 4}, 2, 2), Tile({18, 4}, 2, 2),

                                   Tile({0, 6}, 2, 2),  Tile({2, 6}, 2, 2),  Tile({4, 6}, 2, 2),  Tile({6, 6}, 2, 2),
                                   Tile({8, 6}, 2, 2),  Tile({10, 6}, 2, 2), Tile({12, 6}, 2, 2), Tile({14, 6}, 2, 2),
                                   Tile({16, 6}, 2, 2), Tile({18, 6}, 2, 2),

                                   Tile({0, 8}, 2, 2),  Tile({2, 8}, 2, 2),  Tile({4, 8}, 2, 2),  Tile({6, 8}, 2, 2),
                                   Tile({8, 8}, 2, 2),  Tile({10, 8}, 2, 2), Tile({12, 8}, 2, 2), Tile({14, 8}, 2, 2),
                                   Tile({16, 8}, 2, 2), Tile({18, 8}, 2, 2)}));
    }

    SECTION("testScanlineSequenceWorksCorrectlyNotFullTile") {
        ScanlineSequence scanlineSequence({22, 11}, 5);

        const std::vector<Tile> tiles = scanlineSequence.getTiles();

        REQUIRE(tiles == std::vector<Tile>({Tile({0, 0}, 5, 5), Tile({5, 0}, 5, 5), Tile({10, 0}, 5, 5),
                                            Tile({15, 0}, 5, 5), Tile({20, 0}, 2, 5),

                                            Tile({0, 5}, 5, 5), Tile({5, 5}, 5, 5), Tile({10, 5}, 5, 5),
                                            Tile({15, 5}, 5, 5), Tile({20, 5}, 2, 5),

                                            Tile({0, 10}, 5, 1), Tile({5, 10}, 5, 1), Tile({10, 10}, 5, 1),
                                            Tile({15, 10}, 5, 1), Tile({20, 10}, 2, 1)}));
    }

    SECTION("testScanlineSequenceEmptyImage") {
        ScanlineSequence scanlineSequence({0, 0}, 5);

        const std::vector<Tile> tiles = scanlineSequence.getTiles();

        REQUIRE(tiles.empty());
    }
}

}