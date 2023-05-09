#include "basics/Color.h"
#include "basics/MathUtils.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("MathUtils::lerp") {

    SECTION("should return start value") {
        REQUIRE(MathUtils::lerp(0.f, 0.f, 1.f) == 0);
    }

    SECTION("should return end value") {
        REQUIRE(MathUtils::lerp(1.f, 0.f, 1.f) == 1);
    }

    SECTION("should return value inbetween") {
        REQUIRE(MathUtils::lerp(0.5f, 0.f, 1.f) == 0.5f);
    }

    SECTION("should interpolate colors") {
        REQUIRE(MathUtils::lerp(0.5f, Color::createWhite(), Color::createBlack()) == Color::createGrey(0.5f));
    }
}

TEST_CASE("MathUtils::solveQuadratic") {

    SECTION("should solve linear equation") {
        auto result = MathUtils::solveQuadratic(0, 2, 1);

        REQUIRE(result == QuadraticSolutions{-0.5f, -0.5f});
    }

    SECTION("should return empty optional for non equation") {
        auto result = MathUtils::solveQuadratic(0, 0, 1);

        REQUIRE(result == std::nullopt);
    }

    SECTION("should solve quadratic equation") {
        auto result = MathUtils::solveQuadratic(2, 3, 1);

        REQUIRE(result == QuadraticSolutions{-1.f, -0.5f});
    }

    SECTION("should return empty for no real solution") {
        auto result = MathUtils::solveQuadratic(2, 3, 5);

        REQUIRE(result == std::nullopt);
    }
}

}