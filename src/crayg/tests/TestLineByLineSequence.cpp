#include "image/imageiterators/buckets/LineByLineSequence.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LineByLineSequence::getTiles") {

    SECTION("testLineByLineSequenceWorksCorrectly") {
        LineByLineSequence lineByLineSequence({20, 10}, 2);

        const std::vector<ImageBucket> buckets = lineByLineSequence.getTiles();

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
        LineByLineSequence lineByLineSequence({22, 11}, 5);

        const std::vector<ImageBucket> buckets = lineByLineSequence.getTiles();

        REQUIRE(buckets == std::vector<ImageBucket>(
                               {ImageBucket({0, 0}, 5, 5), ImageBucket({5, 0}, 5, 5), ImageBucket({10, 0}, 5, 5),
                                ImageBucket({15, 0}, 5, 5), ImageBucket({20, 0}, 2, 5),

                                ImageBucket({0, 5}, 5, 5), ImageBucket({5, 5}, 5, 5), ImageBucket({10, 5}, 5, 5),
                                ImageBucket({15, 5}, 5, 5), ImageBucket({20, 5}, 2, 5),

                                ImageBucket({0, 10}, 5, 1), ImageBucket({5, 10}, 5, 1), ImageBucket({10, 10}, 5, 1),
                                ImageBucket({15, 10}, 5, 1), ImageBucket({20, 10}, 2, 1)}));
    }

    SECTION("testLineByLineSequenceEmptyImage") {
        LineByLineSequence lineByLineSequence({0, 0}, 5);

        const std::vector<ImageBucket> buckets = lineByLineSequence.getTiles();

        REQUIRE(buckets.empty());
    }
}

}