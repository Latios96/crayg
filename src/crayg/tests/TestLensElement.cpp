#include "scene/camera/realistic/LensElement.h"
#include <catch2/catch.hpp>

namespace crayg {

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

TEST_CASE("LensElement::intersectCylindricalYElement convex") {

    SECTION("should intersect with cylindrical y element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalYElement(2, -3, Ray({0, 2, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 5);
    }

    SECTION("should not intersect with cylindrical y element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalElement(2, -3, Ray({3, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

TEST_CASE("LensElement::intersectCylindricalYElement concave") {

    SECTION("should intersect with cylindrical y element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalYElement(-2, -3, Ray({0, 2, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 1);
    }

    SECTION("should not intersect with cylindrical y element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalElement(-2, -3, Ray({3, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

TEST_CASE("LensElement::intersectCylindricalXElement convex") {

    SECTION("should intersect with cylindrical x element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalXElement(2, -3, Ray({2, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 5);
    }

    SECTION("should not intersect with cylindrical x element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalXElement(2, -3, Ray({0, 3, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

TEST_CASE("LensElement::intersectCylindricalXElement concave") {

    SECTION("should intersect with cylindrical x element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalXElement(-2, -3, Ray({2, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 1);
    }

    SECTION("should not intersect with cylindrical x element") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalXElement(-2, -3, Ray({0, 3, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

}