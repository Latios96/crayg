#include "scene/camera/realistic/LensElement.h"
#include <catch2/catch.hpp>

namespace crayg {

// convex: positive curvate radius
// concave: negative curvate radius

TEST_CASE("LensElement::intersectSphericalElement convex") {

    SECTION("should intersect with spherical element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalElement(2, -3, Ray({0, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 5);
    }

    SECTION("should not intersect with spherical element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalElement(2, -3, Ray({0, 3, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

TEST_CASE("LensElement::intersectSphericalElement concave") {

    SECTION("should intersect with spherical element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalElement(-2, -3, Ray({0, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 1);
    }

    SECTION("should not intersect with spherical element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalElement(-2, -3, Ray({0, 3, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

}