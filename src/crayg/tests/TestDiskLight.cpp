//
// Created by Jan on 21.11.2020.
//

#include <catch2/catch.hpp>
#include <scene/DiskLight.h>
#include "intersectors/SceneIntersector.h"

namespace crayg {

TEST_CASE("construct DiskLight", "[DiskLight]") {

    SECTION("default construct") {
        DiskLight diskLight;
    }

    SECTION("construct with params") {
        DiskLight diskLight(Transform(), 2, 3);

        REQUIRE(diskLight.getTransform() == Transform());
        REQUIRE(diskLight.getIntensity() == 2);
        REQUIRE(diskLight.getRadius() == 3);
    }
}

struct AreaLightFixture {

    AreaLightFixture() {
        areaLight = std::make_shared<RectLight>();
        position = {0, 2, 2};
        areaLight->setPosition(position);
        areaLight->setWidth(1);
        areaLight->setHeight(1);
        areaLight->setIntensity(1);
        scene.addLight(areaLight);
    }

    std::shared_ptr<RectLight> areaLight;
    Scene scene;
    Vector3f position;
};

TEST_CASE("DiskLight::sampleLightShape") {
    const Vector3f position = {0, 2, 2};
    const float radius = 2;
    DiskLight diskLight(Transform::withPosition(position), 1, radius);


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
    }SECTION("sampleLightShape should respect scale") {

        const Transform transform =
            Transform(Transform::withPosition(position).matrix
                          * Transform::withScale(1. / 2, 1. / 2, 1. / 2).matrix);
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

TEST_CASE("DiskLight isIntersecting", "[DiskLight]") {

    DiskLight diskLight(Transform::withPosition({-3, 0, 0}), 1, 1);

    SECTION("front should intersect") {
        const Ray ray = {{0, 0, 0}, {-1, 0, 0}};

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

    std::shared_ptr<DiskLight> diskLight = std::make_shared<DiskLight>(Transform::withPosition({-3, 0, 0}), 1, 1);

    SECTION("front should intersect") {
        const Ray ray = {{0, 0, 0}, {-1, 0, 0}};

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
    const std::shared_ptr<DiskLight> diskLight = std::make_shared<DiskLight>(Transform::withPosition({0, 0, 0}), 1, 1);

    const BoundingBox bounds = diskLight->getBounds();

    REQUIRE(bounds == BoundingBox({-1, -1, -1}, {1, 1, 1}));
}

}