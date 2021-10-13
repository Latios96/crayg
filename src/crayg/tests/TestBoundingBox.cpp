//
// Created by jan on 30.12.18.
//

#include <catch2/catch.hpp>
#include <basics/BoundingBox.h>

namespace crayg {

TEST_CASE("BoundingBoxIntersection") {
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

TEST_CASE("BoundingBoxUnionWithPoint") {
    BoundingBox boundingBox({0, 0, 0}, {1, 1, 1});

    SECTION("shouldExtendCorrectlyIntoMaxDirection") {
        const BoundingBox unionBoundingBox = boundingBox.unionWith({2, 0, 0});

        REQUIRE(unionBoundingBox == BoundingBox({0, 0, 0}, {2, 1, 1}));
    }

    SECTION("shouldExtendCorrectlyIntoMinDirection") {
        const BoundingBox unionBoundingBox = boundingBox.unionWith({-2, 0, 0});

        REQUIRE(unionBoundingBox == BoundingBox({-2, 0, 0}, {1, 1, 1}));
    }

    SECTION("shouldNotChangeSincePointIsAlreadyIncluded") {
        const BoundingBox unionBoundingBox = boundingBox.unionWith({0.5, 0, 0});

        REQUIRE(unionBoundingBox == BoundingBox({0, 0, 0}, {1, 1, 1}));
    }
}

TEST_CASE("BoundingBoxUnionWithBoundingBox") {
    BoundingBox boundingBox({0, 0, 0}, {1, 1, 1});

    SECTION("shouldExtendCorrectlyIntoMaxDirection") {
        const BoundingBox unionBoundingBox = boundingBox.unionWith({{0, 0, 0}, {2, 0, 0}});

        REQUIRE(unionBoundingBox == BoundingBox({0, 0, 0}, {2, 1, 1}));
    }

    SECTION("shouldExtendCorrectlyIntoMinDirection") {
        const BoundingBox unionBoundingBox = boundingBox.unionWith({{0, 0, 0}, {-2, 0, 0}});

        REQUIRE(unionBoundingBox == BoundingBox({-2, 0, 0}, {1, 1, 1}));
    }

    SECTION("shouldNotChangeSincePointIsAlreadyIncluded") {
        const BoundingBox unionBoundingBox = boundingBox.unionWith({{0, 0, 0}, {0.5, 0, 0}});

        REQUIRE(unionBoundingBox == BoundingBox({0, 0, 0}, {1, 1, 1}));
    }
}

TEST_CASE("BoundingBoxFromCenterAndRadius") {
    const BoundingBox boundingBox = BoundingBox::fromCenterAndRadius({0, 0, 0}, 3);

    REQUIRE(boundingBox == BoundingBox({-3, -3, -3}, {3, 3, 3}));
}

}