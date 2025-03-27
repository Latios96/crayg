#include "scene/camera/realistic/LensSurface.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensSurface::intersectSphericalSurface convex") {

    SECTION("should intersect with spherical surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalSurface(2, -3, Ray({0, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 5);
    }

    SECTION("should not intersect with spherical surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalSurface(2, -3, Ray({0, 3, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

TEST_CASE("LensSurface::intersectSphericalSurface concave") {

    SECTION("should intersect with spherical surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalSurface(-2, -3, Ray({0, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 1);
    }

    SECTION("should not intersect with spherical surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalSurface(-2, -3, Ray({0, 3, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

TEST_CASE("LensSurface::intersectCylindricalYSurface convex") {

    SECTION("should intersect with cylindrical y surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalYSurface(2, -3, Ray({0, 2, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 5);
    }

    SECTION("should not intersect with cylindrical y surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalSurface(2, -3, Ray({3, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

TEST_CASE("LensSurface::intersectCylindricalYSurface concave") {

    SECTION("should intersect with cylindrical y surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalYSurface(-2, -3, Ray({0, 2, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 1);
    }

    SECTION("should not intersect with cylindrical y surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectSphericalSurface(-2, -3, Ray({3, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

TEST_CASE("LensSurface::intersectCylindricalXSurface convex") {

    SECTION("should intersect with cylindrical x surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalXSurface(2, -3, Ray({2, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 5);
    }

    SECTION("should not intersect with cylindrical x surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalXSurface(2, -3, Ray({0, 3, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

TEST_CASE("LensSurface::intersectCylindricalXSurface concave") {

    SECTION("should intersect with cylindrical x surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalXSurface(-2, -3, Ray({2, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 1);
    }

    SECTION("should not intersect with cylindrical x surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectCylindricalXSurface(-2, -3, Ray({0, 3, 0}, {0, 0, -1}), &t, &n);

        REQUIRE_FALSE(intersects);
        REQUIRE(n == Vector3f(0, 0, 0));
        REQUIRE(t == 0);
    }
}

TEST_CASE("LensSurface::intersectPlanarSurface") {

    SECTION("should intersect with planar surface") {
        Vector3f n;
        float t = 0;

        const bool intersects = intersectPlanarSurface(-3, Ray({2, 0, 0}, {0, 0, -1}), &t, &n);

        REQUIRE(intersects);
        REQUIRE(n == Vector3f(0, 0, 1));
        REQUIRE(t == 3);
    }
}

TEST_CASE("LensSurface::scaled") {
    SECTION("should apply scale correctly") {
        LensSurface surface(1, 2, 1.5f, 3, 4, LensMaterial::createMaterialById(LensMaterialId::SCHOTT_N_BK7),
                            LensGeometry::ASPHERICAL, 1);

        const LensSurface scaledSurface = surface.scaled(0.1);

        REQUIRE(scaledSurface == LensSurface(0.1, 0.2, 1.5f, 0.3, 4,
                                             LensMaterial::createMaterialById(LensMaterialId::SCHOTT_N_BK7),
                                             LensGeometry::ASPHERICAL, 1));
    }
}

}