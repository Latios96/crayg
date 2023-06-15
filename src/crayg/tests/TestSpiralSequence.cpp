#include "image/imageiterators/buckets/SpiralSequence.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("SpiralSequence::getTiles") {
    SECTION("should work correctly for square image") {
        Resolution resolution(32, 32);
        SpiralSequence spiralSequence(resolution, 8);

        auto buckets = spiralSequence.getTiles();

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket({16, 8}, 8, 8), ImageBucket({16, 16}, 8, 8), ImageBucket({8, 16}, 8, 8),
                                ImageBucket({8, 8}, 8, 8), ImageBucket({8, 0}, 8, 8), ImageBucket({16, 0}, 8, 8),
                                ImageBucket({24, 0}, 8, 8), ImageBucket({24, 8}, 8, 8), ImageBucket({24, 16}, 8, 8),
                                ImageBucket({24, 24}, 8, 8), ImageBucket({16, 24}, 8, 8), ImageBucket({8, 24}, 8, 8),
                                ImageBucket({0, 24}, 8, 8), ImageBucket({0, 16}, 8, 8), ImageBucket({0, 8}, 8, 8),
                                ImageBucket({0, 0}, 8, 8)}));
    }

    SECTION("should work correctly for landscape rectangular image") {
        Resolution resolution(48, 32);
        SpiralSequence spiralSequence(resolution, 8);

        auto buckets = spiralSequence.getTiles();

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket({24, 8}, 8, 8),  ImageBucket({24, 16}, 8, 8), ImageBucket({16, 16}, 8, 8),
                                ImageBucket({16, 8}, 8, 8),  ImageBucket({16, 0}, 8, 8),  ImageBucket({24, 0}, 8, 8),
                                ImageBucket({32, 0}, 8, 8),  ImageBucket({32, 8}, 8, 8),  ImageBucket({32, 16}, 8, 8),
                                ImageBucket({32, 24}, 8, 8), ImageBucket({24, 24}, 8, 8), ImageBucket({16, 24}, 8, 8),
                                ImageBucket({8, 24}, 8, 8),  ImageBucket({8, 16}, 8, 8),  ImageBucket({8, 8}, 8, 8),
                                ImageBucket({8, 0}, 8, 8),   ImageBucket({40, 0}, 8, 8),  ImageBucket({40, 8}, 8, 8),
                                ImageBucket({40, 16}, 8, 8), ImageBucket({40, 24}, 8, 8), ImageBucket({0, 24}, 8, 8),
                                ImageBucket({0, 16}, 8, 8),  ImageBucket({0, 8}, 8, 8),   ImageBucket({0, 0}, 8, 8)}));
    }

    SECTION("should work correctly for portrait rectangular image") {
        Resolution resolution(32, 48);
        SpiralSequence spiralSequence(resolution, 8);

        auto buckets = spiralSequence.getTiles();

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket({16, 16}, 8, 8), ImageBucket({16, 24}, 8, 8), ImageBucket({8, 24}, 8, 8),
                                ImageBucket({8, 16}, 8, 8),  ImageBucket({8, 8}, 8, 8),   ImageBucket({16, 8}, 8, 8),
                                ImageBucket({24, 8}, 8, 8),  ImageBucket({24, 16}, 8, 8), ImageBucket({24, 24}, 8, 8),
                                ImageBucket({24, 32}, 8, 8), ImageBucket({16, 32}, 8, 8), ImageBucket({8, 32}, 8, 8),
                                ImageBucket({0, 32}, 8, 8),  ImageBucket({0, 24}, 8, 8),  ImageBucket({0, 16}, 8, 8),
                                ImageBucket({0, 8}, 8, 8),   ImageBucket({0, 0}, 8, 8),   ImageBucket({8, 0}, 8, 8),
                                ImageBucket({16, 0}, 8, 8),  ImageBucket({24, 0}, 8, 8),  ImageBucket({24, 40}, 8, 8),
                                ImageBucket({16, 40}, 8, 8), ImageBucket({8, 40}, 8, 8),  ImageBucket({0, 40}, 8, 8)}));
    }

    SECTION("should work correctly for square image which has no integer-multiple width/height of the bucket size") {
        Resolution resolution(30, 30);
        SpiralSequence spiralSequence(resolution, 8);

        auto buckets = spiralSequence.getTiles();

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket({15, 7}, 8, 8), ImageBucket({15, 15}, 8, 8), ImageBucket({7, 15}, 8, 8),
                                ImageBucket({7, 7}, 8, 8), ImageBucket({7, 0}, 8, 7), ImageBucket({15, 0}, 8, 7),
                                ImageBucket({23, 0}, 7, 7), ImageBucket({23, 7}, 7, 8), ImageBucket({23, 15}, 7, 8),
                                ImageBucket({23, 23}, 7, 7), ImageBucket({15, 23}, 8, 7), ImageBucket({7, 23}, 8, 7),
                                ImageBucket({0, 23}, 7, 7), ImageBucket({0, 15}, 7, 8), ImageBucket({0, 7}, 7, 8),
                                ImageBucket({0, 0}, 7, 7)}));
    }

    SECTION("should work correctly for landscape image which has no integer-multiple width/height of the bucket size") {
        Resolution resolution(46, 30);
        SpiralSequence spiralSequence(resolution, 8);

        auto buckets = spiralSequence.getTiles();

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket{{23, 7}, 8, 8},  ImageBucket{{23, 15}, 8, 8}, ImageBucket{{15, 15}, 8, 8},
                                ImageBucket{{15, 7}, 8, 8},  ImageBucket{{15, 0}, 8, 7},  ImageBucket{{23, 0}, 8, 7},
                                ImageBucket{{31, 0}, 8, 7},  ImageBucket{{31, 7}, 8, 8},  ImageBucket{{31, 15}, 8, 8},
                                ImageBucket{{31, 23}, 8, 7}, ImageBucket{{23, 23}, 8, 7}, ImageBucket{{15, 23}, 8, 7},
                                ImageBucket{{7, 23}, 8, 7},  ImageBucket{{7, 15}, 8, 8},  ImageBucket{{7, 7}, 8, 8},
                                ImageBucket{{7, 0}, 8, 7},   ImageBucket{{39, 0}, 7, 7},  ImageBucket{{39, 7}, 7, 8},
                                ImageBucket{{39, 15}, 7, 8}, ImageBucket{{39, 23}, 7, 7}, ImageBucket{{0, 23}, 7, 7},
                                ImageBucket{{0, 15}, 7, 8},  ImageBucket{{0, 7}, 7, 8},   ImageBucket{{0, 0}, 7, 7}}));
    }

    SECTION("should work correctly for portrait image which has no integer-multiple width/height of the bucket size") {
        Resolution resolution(30, 46);
        SpiralSequence spiralSequence(resolution, 8);

        auto buckets = spiralSequence.getTiles();

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket{{15, 15}, 8, 8}, ImageBucket{{15, 23}, 8, 8}, ImageBucket{{7, 23}, 8, 8},
                                ImageBucket{{7, 15}, 8, 8},  ImageBucket{{7, 7}, 8, 8},   ImageBucket{{15, 7}, 8, 8},
                                ImageBucket{{23, 7}, 7, 8},  ImageBucket{{23, 15}, 7, 8}, ImageBucket{{23, 23}, 7, 8},
                                ImageBucket{{23, 31}, 7, 8}, ImageBucket{{15, 31}, 8, 8}, ImageBucket{{7, 31}, 8, 8},
                                ImageBucket{{0, 31}, 7, 8},  ImageBucket{{0, 23}, 7, 8},  ImageBucket{{0, 15}, 7, 8},
                                ImageBucket{{0, 7}, 7, 8},   ImageBucket{{0, 0}, 7, 7},   ImageBucket{{7, 0}, 8, 7},
                                ImageBucket{{15, 0}, 8, 7},  ImageBucket{{23, 0}, 7, 7},  ImageBucket{{23, 39}, 7, 7},
                                ImageBucket{{15, 39}, 8, 7}, ImageBucket{{7, 39}, 8, 7},  ImageBucket{{0, 39}, 7, 7}}));
    }

    SECTION("should work correctly for square image with odd pixel count") {
        Resolution resolution(31, 31);
        SpiralSequence spiralSequence(resolution, 8);

        auto buckets = spiralSequence.getTiles();

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket{{15, 7}, 8, 8}, ImageBucket{{15, 15}, 8, 8}, ImageBucket{{7, 15}, 8, 8},
                                ImageBucket{{7, 7}, 8, 8}, ImageBucket{{7, 0}, 8, 7}, ImageBucket{{15, 0}, 8, 7},
                                ImageBucket{{23, 0}, 8, 7}, ImageBucket{{23, 7}, 8, 8}, ImageBucket{{23, 15}, 8, 8},
                                ImageBucket{{23, 23}, 8, 8}, ImageBucket{{15, 23}, 8, 8}, ImageBucket{{7, 23}, 8, 8},
                                ImageBucket{{0, 23}, 7, 8}, ImageBucket{{0, 15}, 7, 8}, ImageBucket{{0, 7}, 7, 8},
                                ImageBucket{{0, 0}, 7, 7}}));
    }

    SECTION("should work correctly if half the width/height is not a multiple of 8") {
        Resolution resolution(24, 24);
        SpiralSequence spiralSequence(resolution, 8);

        auto buckets = spiralSequence.getTiles();

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket{{12, 4}, 8, 8}, ImageBucket{{12, 12}, 8, 8}, ImageBucket{{4, 12}, 8, 8},
                                ImageBucket{{4, 4}, 8, 8}, ImageBucket{{4, 0}, 8, 4}, ImageBucket{{12, 0}, 8, 4},
                                ImageBucket{{20, 0}, 4, 4}, ImageBucket{{20, 4}, 4, 8}, ImageBucket{{20, 12}, 4, 8},
                                ImageBucket{{20, 20}, 4, 4}, ImageBucket{{12, 20}, 8, 4}, ImageBucket{{4, 20}, 8, 4},
                                ImageBucket{{0, 20}, 4, 4}, ImageBucket{{0, 12}, 4, 8}, ImageBucket{{0, 4}, 4, 8},
                                ImageBucket{{0, 0}, 4, 4}}));
    }

    SECTION("should work correctly if half the width/height is smaller than 8") {
        Resolution resolution(13, 13);
        SpiralSequence spiralSequence(resolution, 8);

        auto buckets = spiralSequence.getTiles();

        REQUIRE(buckets == std::vector<ImageBucket>({ImageBucket{{6, 0}, 7, 6}, ImageBucket{{6, 6}, 7, 7},
                                                     ImageBucket{{0, 6}, 6, 7}, ImageBucket{{0, 0}, 6, 6}}));
    }
}

}