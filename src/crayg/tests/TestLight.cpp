//
// Created by Jan Honsbrok on 06.11.18.
//
#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <sceneIO/Serializable.h>
#include <scene/Scene.h>
#include "scene/Light.h"
#include "intersectors/SceneIntersector.h"

using namespace fakeit;

namespace crayg {

TEST_CASE("serialize Light") {
    Light myLight(Transform::withPosition(Vector3f(1, 2, 3)), 3);

    fakeit::Mock<Serializer> mockSerializer;
    fakeit::When(Method(mockSerializer, writeFloat)).AlwaysReturn();
    fakeit::When(Method(mockSerializer, writeMatrix4x4f)).AlwaysReturn();
    fakeit::When(Method(mockSerializer, writeType)).AlwaysReturn();

    Serializer &s = mockSerializer.get();
    myLight.serialize(s);

    fakeit::Verify(Method(mockSerializer, writeFloat).Using("intensity", 3.0f));
    fakeit::Verify(Method(mockSerializer, writeMatrix4x4f).Using("transform",
                                                                 Transform::withPosition({1, 2, 3}).matrix));
    fakeit::Verify(Method(mockSerializer, writeType).Using("Light"));
}

TEST_CASE("deserialize Light", "[Light]") {

    auto sceneObject = std::make_shared<Light>();

    SECTION("scene containing position should be converted to transform") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, hasProperty).Using("position")).Return(true);
        When(Method(mockDeserializer, readVector3f).Using("position")).Return(Vector3f(1, 2, 3));
        When(Method(mockDeserializer, readMatrix4x4f).Using("transform")).Return(Matrix4x4f());
        When(Method(mockDeserializer, readFloat).Using("intensity")).Return(1);

        Deserializer &s = mockDeserializer.get();
        sceneObject->deserialize(s);

        REQUIRE(sceneObject->getTransform() == Transform::withPosition({1, 2, 3}));
    }

    SECTION("scene containing transform should be read correctly") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, hasProperty).Using("position")).Return(false);
        When(Method(mockDeserializer, readMatrix4x4f).Using("transform")).Return(Matrix4x4f());
        When(Method(mockDeserializer, readMatrix4x4f).Using("transform")).Return(Matrix4x4f());
        When(Method(mockDeserializer, readFloat).Using("intensity")).Return(1);

        Deserializer &s = mockDeserializer.get();
        sceneObject->deserialize(s);

        REQUIRE(sceneObject->getTransform() == Transform());
    }
}

// for some reason fakeit did not work here
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

TEST_CASE("Light Sampling") {
    const float NO_SHADOW = 1.0f;
    const float FULL_SHADOW = 0.0f;

    Light light(Transform::withPosition({0, 5, 0}), 1);

    SECTION("noIntersectionShouldReturnNoShadow") {
        Scene scene;
        MockSceneIntersector mockIntersector(scene, Imageable::Intersection::createInvalid());

        const float shadowFactor = light.calculateShadowFactor(mockIntersector, {0, 0, 0});
        REQUIRE(shadowFactor == NO_SHADOW);
    }

    SECTION("intersectionIsBehindLight") {
        Scene scene;
        MockSceneIntersector mockIntersector(scene, {10, std::make_shared<Sphere>()});

        const float shadowFactor = light.calculateShadowFactor(mockIntersector, {0, 0, 0});
        REQUIRE(shadowFactor == NO_SHADOW);
    }

    SECTION("intersectionIsBeforeLight") {
        Scene scene;
        MockSceneIntersector mockIntersector(scene, {2, std::make_shared<Sphere>()});

        const float shadowFactor = light.calculateShadowFactor(mockIntersector, {0, 0, 0});
        REQUIRE(shadowFactor == FULL_SHADOW);
    }
}

}

