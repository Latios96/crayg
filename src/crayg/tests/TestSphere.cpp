#include <catch2/catch.hpp>
#include <scene/primitives/Sphere.h>

namespace crayg {

TEST_CASE("Sphere") {
    auto mySphere = std::make_shared<Sphere>(Vector3f(0, 0, 0), 3.0f);

    SECTION("createSphere") {
        // make sure radius is correctly set
        REQUIRE(mySphere->getRadius() == 3.0f);
    }

    SECTION("isOccluded") {
        // tests intersecting ray
        Ray intersectingRay(Vector3f(1, 0, 0), Vector3f(-1, 0, 0));
        // intersects should return true
        REQUIRE(mySphere->isIntersecting(intersectingRay));

        // tests not intersecting ray
        Ray notIntersectingRay(Vector3f(0, 0, 5), Vector3f(-1, 0, 0));
        // intersects should return true
        REQUIRE_FALSE(mySphere->isIntersecting(notIntersectingRay));
    }

    SECTION("intersect_") {
        auto mySphere = std::make_shared<Sphere>(Vector3f(1, 0, 0), 3.0f);
        Ray ray(Vector3f(5, 0, 0), Vector3f(-1, 0, 0));

        float t = mySphere->intersect(ray).rayParameter;
        Vector3f hitLocation = ray.constructIntersectionPoint(t);

        REQUIRE(hitLocation.x == Catch::Detail::Approx(4));
        REQUIRE(hitLocation.y == Catch::Detail::Approx(0));
        REQUIRE(hitLocation.z == Catch::Detail::Approx(0));
    }

    SECTION("intersectNotReturnsMax") {
        auto hitRay = mySphere->intersect(Ray(Vector3f(1, 10, -5), Vector3f(0, 0, 1)));
        REQUIRE(hitRay.rayParameter == std::numeric_limits<float>::max());
    }
}

TEST_CASE("Sphere/transformation") {
    auto mySphere = std::make_shared<Sphere>(Vector3f(1, 2, 3), 3.0f);

    REQUIRE(mySphere->getPosition() == Vector3f(1, 2, 3));
}

TEST_CASE("Sphere/intersectsTransformed") {
    auto mySphere = std::make_shared<Sphere>(Vector3f(1, 2, 3), 1.0f);

    REQUIRE(mySphere->isIntersecting(Ray(Vector3f(1, 2, 6), Vector3f(0, 0, -1))));
}

TEST_CASE("Sphere/getBounds") {
    Sphere sphere({1, 2, 3}, 2);

    REQUIRE(sphere.getBounds() == BoundingBox({-1, 0, 1}, {3, 4, 5}));
}

TEST_CASE("Sphere::getPrimitives") {
    Sphere sphere({1, 2, 3}, 2);
    std::vector<Imageable *> target;
    bool isOwning = true;

    sphere.getPrimitives(target, &isOwning);

    REQUIRE(target == std::vector<Imageable *>({&sphere}));
    REQUIRE(isOwning == false);
}

}
