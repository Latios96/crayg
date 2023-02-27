#include "basics/Ray.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("Ray/shouldCreateInvalid", "[Ray]") {
    Ray invalid = Ray::createInvalid();
    REQUIRE_FALSE(invalid.startPoint.isValid());
    REQUIRE_FALSE(invalid.direction.isValid());
    REQUIRE(invalid.length == std::numeric_limits<float>::max());
}

TEST_CASE("Ray/shouldBeInvalid", "[Ray]") {
    Ray invalid = Ray::createInvalid();
    REQUIRE_FALSE(invalid.isValid());
}

TEST_CASE("Ray/constructIntersectionPoint", "[Ray]") {
    Ray ray({1, 2, 3}, {4, 5, 6}, 7);
    Vector3f intersectionPoint = ray.constructIntersectionPoint();
    REQUIRE(intersectionPoint == Vector3f(29, 37, 45));
}

TEST_CASE("Ray/offsetStartPointBy", "[Ray]") {
    Ray ray({0, 0, 0}, {1, 0, 0}, 7);

    const Ray offsetRay = ray.offsetStartPointBy(0.001f);

    REQUIRE(offsetRay == Ray({0.001f, 0, 0}, {1, 0, 0}, 7));
}

}
