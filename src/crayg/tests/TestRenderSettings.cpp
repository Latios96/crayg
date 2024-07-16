#include "scene/RenderSettings.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("RenderSettings::parseRegionFromString") {

    SECTION("should parse region") {
        const Bounds2di parsed = parseRegionFromString("[(0,0),(400,500)]");

        REQUIRE(parsed == Bounds2di({0, 0}, {400, 500}));
    }

    SECTION("should not parse region") {
        REQUIRE_THROWS_WITH(parseRegionFromString("[(0,0),(500)]"),
                            Catch::Equals("Invalid format for region: [(0,0),(500)], supported is [(0,1),(2,3)]"));
    }
}

}