#include "crayg/renderer/TileSizeEstimator.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("TileSizeEstimator::estimateTileSize") {
    const int threadCount = 32;

    SECTION("should estimate less tiles than thread count") {
        const auto testData = GENERATE(table<Resolution, int>({{{200, 200}, 8},
                                                               {{500, 500}, 22},
                                                               {{700, 700}, 30},
                                                               {{800, 800}, 35},
                                                               {{2000, 2000}, 64},
                                                               {{8000, 8000}, 64}}));
        RenderSettings renderSettings;
        renderSettings.resolution = std::get<0>(testData);
        const int expectedTileSize = std::get<1>(testData);
        const TileSizeEstimator tileSizeEstimator(renderSettings);

        const int estimatedTileSize = tileSizeEstimator.estimateTileSize(threadCount);

        REQUIRE(estimatedTileSize == expectedTileSize);
    }
}

}