#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/imageiterators/buckets/ImageBucketSequences.h>

namespace crayg {

TEST_CASE("ImageBucketSequences", "[ImageBucketSequences]") {

    SECTION("testLineByLineSequenceWorksCorrectly") {
        Image image(20, 10);

        const std::vector<ImageBucket> buckets = ImageBucketSequences::lineByLine(image, 2);

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket({0, 0}, 2, 2),  ImageBucket({2, 0}, 2, 2),  ImageBucket({4, 0}, 2, 2),
                                ImageBucket({6, 0}, 2, 2),  ImageBucket({8, 0}, 2, 2),  ImageBucket({10, 0}, 2, 2),
                                ImageBucket({12, 0}, 2, 2), ImageBucket({14, 0}, 2, 2), ImageBucket({16, 0}, 2, 2),
                                ImageBucket({18, 0}, 2, 2),

                                ImageBucket({0, 2}, 2, 2),  ImageBucket({2, 2}, 2, 2),  ImageBucket({4, 2}, 2, 2),
                                ImageBucket({6, 2}, 2, 2),  ImageBucket({8, 2}, 2, 2),  ImageBucket({10, 2}, 2, 2),
                                ImageBucket({12, 2}, 2, 2), ImageBucket({14, 2}, 2, 2), ImageBucket({16, 2}, 2, 2),
                                ImageBucket({18, 2}, 2, 2),

                                ImageBucket({0, 4}, 2, 2),  ImageBucket({2, 4}, 2, 2),  ImageBucket({4, 4}, 2, 2),
                                ImageBucket({6, 4}, 2, 2),  ImageBucket({8, 4}, 2, 2),  ImageBucket({10, 4}, 2, 2),
                                ImageBucket({12, 4}, 2, 2), ImageBucket({14, 4}, 2, 2), ImageBucket({16, 4}, 2, 2),
                                ImageBucket({18, 4}, 2, 2),

                                ImageBucket({0, 6}, 2, 2),  ImageBucket({2, 6}, 2, 2),  ImageBucket({4, 6}, 2, 2),
                                ImageBucket({6, 6}, 2, 2),  ImageBucket({8, 6}, 2, 2),  ImageBucket({10, 6}, 2, 2),
                                ImageBucket({12, 6}, 2, 2), ImageBucket({14, 6}, 2, 2), ImageBucket({16, 6}, 2, 2),
                                ImageBucket({18, 6}, 2, 2),

                                ImageBucket({0, 8}, 2, 2),  ImageBucket({2, 8}, 2, 2),  ImageBucket({4, 8}, 2, 2),
                                ImageBucket({6, 8}, 2, 2),  ImageBucket({8, 8}, 2, 2),  ImageBucket({10, 8}, 2, 2),
                                ImageBucket({12, 8}, 2, 2), ImageBucket({14, 8}, 2, 2), ImageBucket({16, 8}, 2, 2),
                                ImageBucket({18, 8}, 2, 2)}));
    }

    SECTION("testLineByLineSequenceWorksCorrectlyNotFullBucket") {
        Image image(22, 11);

        const std::vector<ImageBucket> buckets = ImageBucketSequences::lineByLine(image, 5);

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket({0, 0}, 5, 5), ImageBucket({5, 0}, 5, 5), ImageBucket({10, 0}, 5, 5),
                                ImageBucket({15, 0}, 5, 5), ImageBucket({20, 0}, 2, 5),

                                ImageBucket({0, 5}, 5, 5), ImageBucket({5, 5}, 5, 5), ImageBucket({10, 5}, 5, 5),
                                ImageBucket({15, 5}, 5, 5), ImageBucket({20, 5}, 2, 5),

                                ImageBucket({0, 10}, 5, 1), ImageBucket({5, 10}, 5, 1), ImageBucket({10, 10}, 5, 1),
                                ImageBucket({15, 10}, 5, 1), ImageBucket({20, 10}, 2, 1)}));
    }

    SECTION("testLineByLineSequenceEmptyImage") {
        Image image(0, 0);

        const std::vector<ImageBucket> buckets = ImageBucketSequences::lineByLine(image, 2);

        REQUIRE(buckets.empty());
    }
}

TEST_CASE("SpiralSequence") {
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
}
}