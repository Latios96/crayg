//
// Created by Jan Honsbrok on 13.11.18.
//

#include <catch2/catch.hpp>
#include "scene/trianglemesh/Triangle.h"
#include "scene/trianglemesh/TriangleMesh.h"
#include <iostream>

namespace crayg {

TEST_CASE("TriangleIntersects") {

    TriangleMesh triangleMesh;
    triangleMesh.points.emplace_back(0, 0, 0);
    triangleMesh.points.emplace_back(0, 1, 0);
    triangleMesh.points.emplace_back(1, 0, 0);
    triangleMesh.faceVertexIndices.emplace_back(0, 1, 2);
    triangleMesh.beforeRender();

    auto TRIANGLE = std::make_shared<Triangle>(&triangleMesh, 0);
    Ray RAY_HITTING_TRIANGLE({0.25f, 0.25f, -1}, {0, 0, 1});
    Ray RAY_MISSING_TRIANGLE_LEFT({-1, 0.25f, -1}, {0, 0, 1});
    Ray RAY_MISSING_TRIANGLE_TOP({0.25f, 1, -1}, {0, 0, 1});
    Ray RAY_MISSING_TRIANGLE_BOTTOM({0.25f, -1, -1}, {0, 0, 1});
    Ray RAY_MISSING_TRIANGLE_PARALLEL({-1, 0.25f, -1}, {1, 0, 0});

    SECTION("intersectsShouldBeTrue") {
        REQUIRE(TRIANGLE->isIntersecting(RAY_HITTING_TRIANGLE));
    }

    SECTION("intersectsShouldBeFalse") {
        REQUIRE_FALSE(TRIANGLE->isIntersecting(RAY_MISSING_TRIANGLE_LEFT));
        REQUIRE_FALSE(TRIANGLE->isIntersecting(RAY_MISSING_TRIANGLE_TOP));
        REQUIRE_FALSE(TRIANGLE->isIntersecting(RAY_MISSING_TRIANGLE_BOTTOM));
    }

    SECTION("intersectsShouldBeFalseParallel") {
        REQUIRE_FALSE(TRIANGLE->isIntersecting(RAY_MISSING_TRIANGLE_PARALLEL));
    }

    SECTION("intersectShouldBeValid") {
        REQUIRE(TRIANGLE->intersect(RAY_HITTING_TRIANGLE).isValid());
    }

    SECTION("intersectShouldBeInValid") {
        REQUIRE_FALSE(TRIANGLE->intersect(RAY_MISSING_TRIANGLE_LEFT).isValid());
        REQUIRE_FALSE(TRIANGLE->intersect(RAY_MISSING_TRIANGLE_TOP).isValid());
        REQUIRE_FALSE(TRIANGLE->intersect(RAY_MISSING_TRIANGLE_BOTTOM).isValid());
    }

    SECTION("intersectShouldBeInvalid") {
        REQUIRE_FALSE(TRIANGLE->intersect(RAY_MISSING_TRIANGLE_PARALLEL).isValid());
    }

    SECTION("hitRayShouldHaveCorrectLength") {
        auto hitIntersection = TRIANGLE->intersect(RAY_HITTING_TRIANGLE);
        REQUIRE(hitIntersection.rayParameter == 1);
    }

    SECTION("hitLocationCaBeCorrectlyConstructed") {
        auto hitIntersection = TRIANGLE->intersect(RAY_HITTING_TRIANGLE);
        const Vector3f hitRay = RAY_HITTING_TRIANGLE.constructIntersectionPoint(hitIntersection.rayParameter);
        REQUIRE(hitRay == Vector3f(0.25f, 0.25f, 0));
    }
}

TEST_CASE("TriangleGetBounds") {
    TriangleMesh triangleMesh;
    triangleMesh.points.emplace_back(0, 0, 0);
    triangleMesh.points.emplace_back(0, 1, 0);
    triangleMesh.points.emplace_back(1, 0, 0);
    triangleMesh.faceVertexIndices.emplace_back(0, 1, 2);
    triangleMesh.beforeRender();

    Triangle triangle(&triangleMesh, 0);

    const BoundingBox boundingBox = triangle.getBounds();

    REQUIRE(boundingBox == BoundingBox({0, 0, 0}, {1, 1, 0}));
}

}
