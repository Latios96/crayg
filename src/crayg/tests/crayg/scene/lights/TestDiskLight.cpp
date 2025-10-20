#include "crayg/renderer/intersectors/SceneIntersector.h"
#include "crayg/scene/lights/DiskLight.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("construct DiskLight", "[DiskLight]") {

    SECTION("default construct") {
        DiskLight diskLight;
    }

    SECTION("construct with params") {
        DiskLight diskLight(Transform(), 2.0f, 3.0f);

        REQUIRE(diskLight.getTransform() == Transform());
        REQUIRE(diskLight.getIntensity() == 2);
        REQUIRE(diskLight.getRadius() == 3);
    }
}

TEST_CASE("DiskLight::sampleLightShape") {
    const Vector3f position = {0, 2, 2};
    const float radius = 2;
    DiskLight diskLight(Transform::withPosition(position), 1.0f, radius);

    SECTION("sampleLightShape should respect radius") {
        const float realRadius = 2;
        for (int i = 0; i < 1000; i++) {
            const Vector3f samplePoint = diskLight.sampleLightShape();
            REQUIRE(samplePoint.x < (position.x + realRadius));
            REQUIRE(samplePoint.x > (position.x - realRadius));
            REQUIRE(samplePoint.y < (position.y + realRadius));
            REQUIRE(samplePoint.y > (position.y - realRadius));
            REQUIRE(samplePoint.z == position.z);
        }
    }
    SECTION("sampleLightShape should respect scale") {

        const Transform transform = Transform::withPosition(position) * Transform::withScale(1. / 2, 1. / 2, 1. / 2);
        diskLight.setTransform(transform);
        const float realRadius = 1;

        for (int i = 0; i < 1000; i++) {
            const Vector3f samplePoint = diskLight.sampleLightShape();
            REQUIRE(samplePoint.x < (position.x + realRadius));
            REQUIRE(samplePoint.x > (position.x - realRadius));
            REQUIRE(samplePoint.y < (position.y + realRadius));
            REQUIRE(samplePoint.y > (position.y - realRadius));
            REQUIRE(samplePoint.z == position.z);
        }
    }
}

TEST_CASE("DiskLight isOccluded", "[DiskLight]") {

    DiskLight diskLight(Transform::withPosition({0, 0, -3}), 1.0f, 1.0f);

    SECTION("front should intersect") {
        const Ray ray = {{0, 0, 0}, {0, 0, -1}};

        const bool isIntersecting = diskLight.isIntersecting(ray);

        REQUIRE(isIntersecting);
    }

    SECTION("back should not intersect") {
        const Ray ray = {{-6, 0, 0}, {1, 0, 0}};

        const bool isIntersecting = diskLight.isIntersecting(ray);

        REQUIRE_FALSE(isIntersecting);
    }
}

TEST_CASE("DiskLight intersect", "[DiskLight]") {

    std::shared_ptr<DiskLight> diskLight = std::make_shared<DiskLight>(Transform::withPosition({0, 0, -3}), 1.0f, 1.0f);

    SECTION("front should intersect") {
        const Ray ray = {{0, 0, 0}, {0, 0, -1}};

        const Imageable::Intersection intersection = diskLight->intersect(ray);

        REQUIRE(intersection.imageable);
    }

    SECTION("back should not intersect") {
        const Ray ray = {{-6, 0, 0}, {1, 0, 0}};

        const Imageable::Intersection intersection = diskLight->intersect(ray);

        REQUIRE(intersection.imageable == nullptr);
    }
}

TEST_CASE("Disklight getBounds", "[DiskLight]") {
    const std::shared_ptr<DiskLight> diskLight =
        std::make_shared<DiskLight>(Transform::withPosition({0, 0, 0}), 1.0f, 1.0f);

    const BoundingBox bounds = diskLight->getBounds();

    REQUIRE(bounds == BoundingBox({-1, -1, -1}, {1, 1, 1}));
}

TEST_CASE("Disklight::area") {
    const Vector3f position = {0, 2, 2};
    const float radius = 2;
    DiskLight diskLight(Transform::withPosition(position), 1.0f, radius);

    SECTION("area should respect width and height") {
        const float area = diskLight.area();

        REQUIRE(area == Catch::Detail::Approx(12.56637f));
    }

    SECTION("area should respect scale") {
        diskLight.setRadius(1);
        const Transform transform = Transform::withPosition(position) * Transform::withScale(5, 5, 5);
        diskLight.setTransform(transform);

        const float area = diskLight.area();

        REQUIRE(area == Catch::Detail::Approx(78.53982f));
    }
}

}