#include "crayg/scene/primitives/GroundPlane.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("GroundPlaneIntersection") {

    GroundPlane myGroundPlane;

    Ray NOT_PARALLEL_RAY({0, 1, 0}, {0, -1, -1});
    Ray PARALLEL_RAY({0, 1, 0}, {0, 0, -1});

    SECTION("NotParallelRayIsIntersecting") {
        REQUIRE(myGroundPlane.isIntersecting(NOT_PARALLEL_RAY));
    }

    SECTION("ParallelRayIsNotIntersecting") {
        REQUIRE_FALSE(myGroundPlane.isIntersecting(PARALLEL_RAY));
    }

    SECTION("NotParallelRayReturnsCorrectIntersection") {
        Imageable::Intersection intersection = myGroundPlane.intersect(NOT_PARALLEL_RAY);
        REQUIRE(intersection.imageable == &myGroundPlane);
        REQUIRE(intersection.rayParameter == 1.0f);
    }

    SECTION("ParallelRayReturnsInvalidIntersection") {
        Imageable::Intersection intersection = myGroundPlane.intersect(PARALLEL_RAY);
        REQUIRE_FALSE(intersection.isValid());
    }
}

TEST_CASE("GroundPlaneIntersectionGetBounds") {
    std::shared_ptr<GroundPlane> myGroundPlane = std::make_shared<GroundPlane>();

    const BoundingBox bounds = myGroundPlane->getBounds();

    REQUIRE(bounds == BoundingBox({std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(),
                                   std::numeric_limits<float>::lowest()},
                                  {std::numeric_limits<float>::max(), 0, std::numeric_limits<float>::max()}));
}

TEST_CASE("GroundPlaneIntersectionGetBounds::getPrimitives") {
    GroundPlane groundPlane;

    std::vector<Imageable *> target;

    groundPlane.getPrimitives(target);

    REQUIRE(target == std::vector<Imageable *>({&groundPlane}));
}

}