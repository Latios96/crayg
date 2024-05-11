#include "utils/Heatmap.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("HeatMap::lookup") {

    SECTION("should clamp negative to 0") {
        const Color color = MagmaHeatmap::lookup(-1);

        REQUIRE(color == Color(0.001462, 0.000466, 0.013866));
    }

    SECTION("should clamp nan to 0") {
        const Color color = MagmaHeatmap::lookup(std::nan(""));

        REQUIRE(color == Color(0.001462, 0.000466, 0.013866));
    }

    SECTION("should clamp to 1") {
        const Color color = MagmaHeatmap::lookup(2);

        REQUIRE(color == Color({0.987053, 0.991438, 0.749504}));
    }

    SECTION("should lookup correctly") {
        const Color color = MagmaHeatmap::lookup(0.5f);

        REQUIRE(color == Color(0.709962, 0.212797, 0.477201));
    }
}

}