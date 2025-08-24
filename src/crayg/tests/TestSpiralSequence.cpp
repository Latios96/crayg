#include "crayg/foundation/areaiterators/tiles/SpiralSequence.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("SpiralSequence::getTiles") {
    SECTION("should work correctly for square image") {
        Resolution resolution(32, 32);
        SpiralSequence spiralSequence(resolution, 8);

        auto tiles = spiralSequence.getTiles();

        REQUIRE(tiles == std::vector<Tile>(
                             {Tile({16, 8}, 8, 8), Tile({16, 16}, 8, 8), Tile({8, 16}, 8, 8), Tile({8, 8}, 8, 8),
                              Tile({8, 0}, 8, 8), Tile({16, 0}, 8, 8), Tile({24, 0}, 8, 8), Tile({24, 8}, 8, 8),
                              Tile({24, 16}, 8, 8), Tile({24, 24}, 8, 8), Tile({16, 24}, 8, 8), Tile({8, 24}, 8, 8),
                              Tile({0, 24}, 8, 8), Tile({0, 16}, 8, 8), Tile({0, 8}, 8, 8), Tile({0, 0}, 8, 8)}));
    }

    SECTION("should work correctly for landscape rectangular image") {
        Resolution resolution(48, 32);
        SpiralSequence spiralSequence(resolution, 8);

        auto tiles = spiralSequence.getTiles();

        REQUIRE(tiles == std::vector<Tile>(
                             {Tile({24, 8}, 8, 8),  Tile({24, 16}, 8, 8), Tile({16, 16}, 8, 8), Tile({16, 8}, 8, 8),
                              Tile({16, 0}, 8, 8),  Tile({24, 0}, 8, 8),  Tile({32, 0}, 8, 8),  Tile({32, 8}, 8, 8),
                              Tile({32, 16}, 8, 8), Tile({32, 24}, 8, 8), Tile({24, 24}, 8, 8), Tile({16, 24}, 8, 8),
                              Tile({8, 24}, 8, 8),  Tile({8, 16}, 8, 8),  Tile({8, 8}, 8, 8),   Tile({8, 0}, 8, 8),
                              Tile({40, 0}, 8, 8),  Tile({40, 8}, 8, 8),  Tile({40, 16}, 8, 8), Tile({40, 24}, 8, 8),
                              Tile({0, 24}, 8, 8),  Tile({0, 16}, 8, 8),  Tile({0, 8}, 8, 8),   Tile({0, 0}, 8, 8)}));
    }

    SECTION("should work correctly for portrait rectangular image") {
        Resolution resolution(32, 48);
        SpiralSequence spiralSequence(resolution, 8);

        auto tiles = spiralSequence.getTiles();

        REQUIRE(tiles == std::vector<Tile>(
                             {Tile({16, 16}, 8, 8), Tile({16, 24}, 8, 8), Tile({8, 24}, 8, 8),  Tile({8, 16}, 8, 8),
                              Tile({8, 8}, 8, 8),   Tile({16, 8}, 8, 8),  Tile({24, 8}, 8, 8),  Tile({24, 16}, 8, 8),
                              Tile({24, 24}, 8, 8), Tile({24, 32}, 8, 8), Tile({16, 32}, 8, 8), Tile({8, 32}, 8, 8),
                              Tile({0, 32}, 8, 8),  Tile({0, 24}, 8, 8),  Tile({0, 16}, 8, 8),  Tile({0, 8}, 8, 8),
                              Tile({0, 0}, 8, 8),   Tile({8, 0}, 8, 8),   Tile({16, 0}, 8, 8),  Tile({24, 0}, 8, 8),
                              Tile({24, 40}, 8, 8), Tile({16, 40}, 8, 8), Tile({8, 40}, 8, 8),  Tile({0, 40}, 8, 8)}));
    }

    SECTION("should work correctly for square image which has no integer-multiple width/height of the tile size") {
        Resolution resolution(30, 30);
        SpiralSequence spiralSequence(resolution, 8);

        auto tiles = spiralSequence.getTiles();

        REQUIRE(tiles == std::vector<Tile>(
                             {Tile({15, 7}, 8, 8), Tile({15, 15}, 8, 8), Tile({7, 15}, 8, 8), Tile({7, 7}, 8, 8),
                              Tile({7, 0}, 8, 7), Tile({15, 0}, 8, 7), Tile({23, 0}, 7, 7), Tile({23, 7}, 7, 8),
                              Tile({23, 15}, 7, 8), Tile({23, 23}, 7, 7), Tile({15, 23}, 8, 7), Tile({7, 23}, 8, 7),
                              Tile({0, 23}, 7, 7), Tile({0, 15}, 7, 8), Tile({0, 7}, 7, 8), Tile({0, 0}, 7, 7)}));
    }

    SECTION("should work correctly for landscape image which has no integer-multiple width/height of the tile size") {
        Resolution resolution(46, 30);
        SpiralSequence spiralSequence(resolution, 8);

        auto tiles = spiralSequence.getTiles();

        REQUIRE(tiles == std::vector<Tile>(
                             {Tile{{23, 7}, 8, 8},  Tile{{23, 15}, 8, 8}, Tile{{15, 15}, 8, 8}, Tile{{15, 7}, 8, 8},
                              Tile{{15, 0}, 8, 7},  Tile{{23, 0}, 8, 7},  Tile{{31, 0}, 8, 7},  Tile{{31, 7}, 8, 8},
                              Tile{{31, 15}, 8, 8}, Tile{{31, 23}, 8, 7}, Tile{{23, 23}, 8, 7}, Tile{{15, 23}, 8, 7},
                              Tile{{7, 23}, 8, 7},  Tile{{7, 15}, 8, 8},  Tile{{7, 7}, 8, 8},   Tile{{7, 0}, 8, 7},
                              Tile{{39, 0}, 7, 7},  Tile{{39, 7}, 7, 8},  Tile{{39, 15}, 7, 8}, Tile{{39, 23}, 7, 7},
                              Tile{{0, 23}, 7, 7},  Tile{{0, 15}, 7, 8},  Tile{{0, 7}, 7, 8},   Tile{{0, 0}, 7, 7}}));
    }

    SECTION("should work correctly for portrait image which has no integer-multiple width/height of the tile size") {
        Resolution resolution(30, 46);
        SpiralSequence spiralSequence(resolution, 8);

        auto tiles = spiralSequence.getTiles();

        REQUIRE(tiles == std::vector<Tile>(
                             {Tile{{15, 15}, 8, 8}, Tile{{15, 23}, 8, 8}, Tile{{7, 23}, 8, 8},  Tile{{7, 15}, 8, 8},
                              Tile{{7, 7}, 8, 8},   Tile{{15, 7}, 8, 8},  Tile{{23, 7}, 7, 8},  Tile{{23, 15}, 7, 8},
                              Tile{{23, 23}, 7, 8}, Tile{{23, 31}, 7, 8}, Tile{{15, 31}, 8, 8}, Tile{{7, 31}, 8, 8},
                              Tile{{0, 31}, 7, 8},  Tile{{0, 23}, 7, 8},  Tile{{0, 15}, 7, 8},  Tile{{0, 7}, 7, 8},
                              Tile{{0, 0}, 7, 7},   Tile{{7, 0}, 8, 7},   Tile{{15, 0}, 8, 7},  Tile{{23, 0}, 7, 7},
                              Tile{{23, 39}, 7, 7}, Tile{{15, 39}, 8, 7}, Tile{{7, 39}, 8, 7},  Tile{{0, 39}, 7, 7}}));
    }

    SECTION("should work correctly for square image with odd pixel count") {
        Resolution resolution(31, 31);
        SpiralSequence spiralSequence(resolution, 8);

        auto tiles = spiralSequence.getTiles();

        REQUIRE(tiles == std::vector<Tile>(
                             {Tile{{15, 7}, 8, 8}, Tile{{15, 15}, 8, 8}, Tile{{7, 15}, 8, 8}, Tile{{7, 7}, 8, 8},
                              Tile{{7, 0}, 8, 7}, Tile{{15, 0}, 8, 7}, Tile{{23, 0}, 8, 7}, Tile{{23, 7}, 8, 8},
                              Tile{{23, 15}, 8, 8}, Tile{{23, 23}, 8, 8}, Tile{{15, 23}, 8, 8}, Tile{{7, 23}, 8, 8},
                              Tile{{0, 23}, 7, 8}, Tile{{0, 15}, 7, 8}, Tile{{0, 7}, 7, 8}, Tile{{0, 0}, 7, 7}}));
    }

    SECTION("should work correctly if half the width/height is not a multiple of 8") {
        Resolution resolution(24, 24);
        SpiralSequence spiralSequence(resolution, 8);

        auto tiles = spiralSequence.getTiles();

        REQUIRE(tiles == std::vector<Tile>(
                             {Tile{{12, 4}, 8, 8}, Tile{{12, 12}, 8, 8}, Tile{{4, 12}, 8, 8}, Tile{{4, 4}, 8, 8},
                              Tile{{4, 0}, 8, 4}, Tile{{12, 0}, 8, 4}, Tile{{20, 0}, 4, 4}, Tile{{20, 4}, 4, 8},
                              Tile{{20, 12}, 4, 8}, Tile{{20, 20}, 4, 4}, Tile{{12, 20}, 8, 4}, Tile{{4, 20}, 8, 4},
                              Tile{{0, 20}, 4, 4}, Tile{{0, 12}, 4, 8}, Tile{{0, 4}, 4, 8}, Tile{{0, 0}, 4, 4}}));
    }

    SECTION("should work correctly if half the width/height is smaller than 8") {
        Resolution resolution(13, 13);
        SpiralSequence spiralSequence(resolution, 8);

        auto tiles = spiralSequence.getTiles();

        REQUIRE(tiles ==
                std::vector<Tile>({Tile{{6, 0}, 7, 6}, Tile{{6, 6}, 7, 7}, Tile{{0, 6}, 6, 7}, Tile{{0, 0}, 6, 6}}));
    }
}

}