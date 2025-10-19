#include "basics/Color.h"
#include "crayg/foundation/math/CommonMath.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("CommonMath::lerp") {

    SECTION("should return start value") {
        REQUIRE(CommonMath::lerp(0.f, 0.f, 1.f) == 0);
    }

    SECTION("should return end value") {
        REQUIRE(CommonMath::lerp(1.f, 0.f, 1.f) == 1);
    }

    SECTION("should return value inbetween") {
        REQUIRE(CommonMath::lerp(0.5f, 0.f, 1.f) == 0.5f);
    }

    SECTION("should interpolate colors") {
        REQUIRE(CommonMath::lerp(0.5f, Color::createWhite(), Color::createBlack()) == Color::createGrey(0.5f));
    }
}

}