//
// Created by Jan on 21.11.2020.
//

#include <catch2/catch.hpp>
#include <scene/DiskLight.h>
#include <fakeit.hpp>
#include "intersectors/SceneIntersector.h"

using namespace fakeit;

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

TEST_CASE("serialize DiskLight", "[DiskLight]") {
    DiskLight diskLight(Transform(), 2, 3);

    fakeit::Mock<Serializer> mockSerializer;
    fakeit::When(Method(mockSerializer, writeFloat)).AlwaysReturn();
    fakeit::When(Method(mockSerializer, writeMatrix4x4f)).AlwaysReturn();
    fakeit::When(Method(mockSerializer, writeType)).AlwaysReturn();

    Serializer &s = mockSerializer.get();
    diskLight.serialize(s);

    fakeit::Verify(Method(mockSerializer, writeFloat).Using("intensity", 2.0f));
    fakeit::Verify(Method(mockSerializer, writeFloat).Using("radius", 3.0f));
    fakeit::Verify(Method(mockSerializer, writeMatrix4x4f).Using("transform",
                                                                 Transform().matrix));
    fakeit::Verify(Method(mockSerializer, writeType).Using("DiskLight"));
}

TEST_CASE("deserialize DiskLight", "[DiskLight]") {
    DiskLight diskLight;

    fakeit::Mock<Deserializer> mockDeserializer;
    When(Method(mockDeserializer, hasProperty).Using("position")).Return(false);
    When(Method(mockDeserializer, readMatrix4x4f).Using("transform")).Return(Matrix4x4f());
    When(Method(mockDeserializer, readFloat).Using("intensity")).Return(2);
    When(Method(mockDeserializer, readFloat).Using("radius")).Return(3);

    Deserializer &s = mockDeserializer.get();
    diskLight.deserialize(s);

    REQUIRE(diskLight.getTransform() == Transform());
    REQUIRE(diskLight.getIntensity() == 2);
    REQUIRE(diskLight.getRadius() == 3);
}

class MockSceneIntersector : public SceneIntersector {
 public:
    MockSceneIntersector(Scene &scene, const Imageable::Intersection &return_value)
        : SceneIntersector(scene) {
        this->return_value = return_value;
    }
    Imageable::Intersection intersect(const Ray &ray) const override {
        return return_value;
    };
 private:
    Imageable::Intersection return_value;
};

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
/*
TEST_CASE("DiskLight shadowFactor", "[DiskLight]") {

    SECTION("Disklight at origin should have full light") {
        Scene scene;
        DiskLight diskLight;
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection::createInvalid());

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {3, 0, 0});

        REQUIRE(shadowFactor == 1);
    }

    SECTION("Disklight at origin should have no light behind") {
        Scene scene;
        DiskLight diskLight;
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection::createInvalid());

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {-3, 0, 0});

        REQUIRE(shadowFactor == 0);
    }

    SECTION("Disklight at origin should have no light because of intersection") {
        Scene scene;
        DiskLight diskLight;
        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection(2, sphere->shared_from_this()));

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {3, 0, 0});

        REQUIRE(shadowFactor == 0);
    }

    SECTION("Disklight moved behind should have full light") {
        Scene scene;
        DiskLight diskLight(Transform::withPosition({-3, 0, 0}), 1, 1);
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection::createInvalid());

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {3, 0, 0});

        REQUIRE(shadowFactor == 1);
    }

    SECTION("Disklight moved behind should have no light behind") {
        Scene scene;
        DiskLight diskLight(Transform::withPosition({-3, 0, 0}), 1, 1);
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection::createInvalid());

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {-4, 0, 0});

        REQUIRE(shadowFactor == 0);
    }

    SECTION("Disklight moved behind should have no light because of intersection") {
        Scene scene;
        DiskLight diskLight(Transform::withPosition({-3, 0, 0}), 1, 1);
        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection(2, sphere->shared_from_this()));

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {3, 0, 0});

        REQUIRE(shadowFactor == 0);
    }

    SECTION("Disklight moved front should have full light") {
        Scene scene;
        DiskLight diskLight(Transform::withPosition({3, 0, 0}), 1, 1);
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection::createInvalid());

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {6, 0, 0});

        REQUIRE(shadowFactor == 1);
    }

    SECTION("Disklight moved front should have no light behind") {
        Scene scene;
        DiskLight diskLight(Transform::withPosition({3, 0, 0}), 1, 1);
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection::createInvalid());

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {-4, 0, 0});

        REQUIRE(shadowFactor == 0);
    }

    SECTION("Disklight moved front should have no light because of intersection") {
        Scene scene;
        DiskLight diskLight(Transform::withPosition({3, 0, 0}), 1, 1);
        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection(2, sphere->shared_from_this()));

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {6, 0, 0});

        REQUIRE(shadowFactor == 0);
    }

    SECTION("Disklight rotated should have full light") {
        Scene scene;
        DiskLight diskLight(Transform::withRotation(0, 0, -90), 1, 1);
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection::createInvalid());

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {0, -6, 0});

        REQUIRE(shadowFactor == 1);
    }

    SECTION("Disklight rotated up should have no light behind") {
        Scene scene;
        DiskLight diskLight(Transform::withRotation(0, 0, -90), 1, 1);
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection::createInvalid());

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {0, 6, 0});

        REQUIRE(shadowFactor == 0);
    }

    SECTION("Disklight rotated up should have no light because of intersection") {
        Scene scene;
        DiskLight diskLight(Transform::withRotation(0, 0, -90), 1, 1);
        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
        MockSceneIntersector mockSceneIntersector(scene, Imageable::Intersection(-2, sphere->shared_from_this()));

        const float shadowFactor = diskLight.calculateShadowFactor(mockSceneIntersector, {0, -6, 0});

        REQUIRE(shadowFactor == 0);
    }

}*/

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