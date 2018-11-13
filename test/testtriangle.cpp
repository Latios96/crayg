//
// Created by Jan Honsbrok on 13.11.18.
//

#include <catch.hpp>
#include <scene/Triangle.h>
#include "utils/utils.h"


TEST_CASE("TriangleIntersects") {

    Triangle TRIANGLE({0,0,0},{0,1,0},{1,0,0});
    Ray RAY_HITTING_TRIANGLE({0.25f,0.25f, -1}, {0,0,1});
    Ray RAY_MISSING_TRIANGLE_LEFT({-1,0.25f, -1}, {0,0,1});
    Ray RAY_MISSING_TRIANGLE_TOP({0.25f,1, -1}, {0,0,1});
    Ray RAY_MISSING_TRIANGLE_BOTTOM({0.25f,-1, -1}, {0,0,1});
    Ray RAY_MISSING_TRIANGLE_PARALLEL({-1,0.25f, -1}, {1,0,0});

    SECTION("intersectsShouldBeTrue") {
        REQUIRE(TRIANGLE.intersects(RAY_HITTING_TRIANGLE));
    }

    SECTION("intersectsShouldBeFalse") {
        REQUIRE_FALSE(TRIANGLE.intersects(RAY_MISSING_TRIANGLE_LEFT));
        REQUIRE_FALSE(TRIANGLE.intersects(RAY_MISSING_TRIANGLE_TOP));
        REQUIRE_FALSE(TRIANGLE.intersects(RAY_MISSING_TRIANGLE_BOTTOM));
    }

    SECTION("intersectsShouldBeFalseParallel") {
        REQUIRE_FALSE(TRIANGLE.intersects(RAY_MISSING_TRIANGLE_PARALLEL));
    }

    SECTION("intersectShouldBeValid") {
        REQUIRE(TRIANGLE.intersect(RAY_HITTING_TRIANGLE).isValid());
    }

    SECTION("intersectShouldBeInValid") {
        REQUIRE_FALSE(TRIANGLE.intersect(RAY_MISSING_TRIANGLE_LEFT).isValid());
        REQUIRE_FALSE(TRIANGLE.intersect(RAY_MISSING_TRIANGLE_TOP).isValid());
        REQUIRE_FALSE(TRIANGLE.intersect(RAY_MISSING_TRIANGLE_BOTTOM).isValid());
    }

    SECTION("intersectShouldBeInvalid") {
        REQUIRE_FALSE(TRIANGLE.intersect(RAY_MISSING_TRIANGLE_PARALLEL).isValid());
    }

    SECTION("hitRayShouldHaveCorrectLength") {
        auto hitRay = TRIANGLE.intersect(RAY_HITTING_TRIANGLE);
        REQUIRE(hitRay.length == 1);
    }

    SECTION("hitLocationCaBeCorrectlyConstructed") {
        auto hitRay = TRIANGLE.intersect(RAY_HITTING_TRIANGLE);
        REQUIRE(hitRay.constructIntersectionPoint() == Vector3f(0.25f, 0.25f, 0));
    }
}
