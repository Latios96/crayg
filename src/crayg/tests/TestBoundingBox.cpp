//
// Created by jan on 30.12.18.
//

#include <catch2/catch.hpp>
#include <foundation/BoundingBox.h>

TEST_CASE("BoundingBox") {
    BoundingBox boundingBox({0, 0, 0}, {1, 1, 1});

    Ray RAY_IS_INTERSECTING({0.5f, 0.5f, -1}, {0, 0, 1});
    Ray RAY_IS_NOT_INTERSECTING({-0.5f, -0.5f, -1}, {0, 0, 1});

    SECTION("shouldIntersect") {
        REQUIRE(boundingBox.isIntersecting(RAY_IS_INTERSECTING));
    }

    SECTION("shouldNotIntersect") {
        REQUIRE_FALSE(boundingBox.isIntersecting(RAY_IS_NOT_INTERSECTING));
    }
}