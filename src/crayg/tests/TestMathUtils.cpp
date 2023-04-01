#include "basics/MathUtils.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("MathUtils::lerp") {

    SECTION("should return start value") {
        REQUIRE(MathUtils::lerp<float>(0, 0, 1) == 0);
    }

    SECTION("should return end value") {
        REQUIRE(MathUtils::lerp<float>(1, 0, 1) == 1);
    }

    SECTION("should return value inbetween") {
        REQUIRE(MathUtils::lerp<float>(0.5f, 0, 1) == 0.5f);
    }
}

}