#include "crayg/foundation/math/QuadraticEquations.h"
#include "crayg/foundation/math/geometry/Color.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("QuadraticEquations::solveQuadratic") {

    SECTION("should solve linear equation") {
        auto result = QuadraticEquations::solveQuadratic(0, 2, 1);

        REQUIRE(result == QuadraticSolutions{-0.5f, -0.5f});
    }

    SECTION("should return empty optional for non equation") {
        auto result = QuadraticEquations::solveQuadratic(0, 0, 1);

        REQUIRE(result == std::nullopt);
    }

    SECTION("should solve quadratic equation") {
        auto result = QuadraticEquations::solveQuadratic(2, 3, 1);

        REQUIRE(result == QuadraticSolutions{-1.f, -0.5f});
    }

    SECTION("should return empty for no real solution") {
        auto result = QuadraticEquations::solveQuadratic(2, 3, 5);

        REQUIRE(result == std::nullopt);
    }
}

}