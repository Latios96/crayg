//
// Created by Jan on 10.11.2020.
//
#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <sceneIO/read/Deserializer.h>
#include <scene/SceneObject.h>

using namespace fakeit;

class SceneObjectForTesting : public SceneObject {
 public:
    Vector3f getNormal(Vector3f point) override {
        return {};
    }
    Intersection intersect(Ray ray) override {
        return Intersection();
    }
    bool isIntersecting(Ray ray) override {
        return false;
    }
};

TEST_CASE("deserialize SceneObject", "[SceneObject]") {

    auto sceneObject = std::make_shared<SceneObjectForTesting>();

    SECTION("scene containing position should be converted to transform") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, hasProperty).Using("position")).Return(true);
        When(Method(mockDeserializer, readVector3f).Using("position")).Return(Vector3f(1, 2, 3));

        Deserializer &s = mockDeserializer.get();
        sceneObject->deserialize(s);

        REQUIRE(sceneObject->getTransform() == Transform::fromPosition({1, 2, 3}));
    }

    SECTION("scene containing transform should be read correctly") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, hasProperty).Using("position")).Return(false);
        When(Method(mockDeserializer, readMatrix4x4f).Using("transform")).Return(Matrix4x4f());

        Deserializer &s = mockDeserializer.get();
        sceneObject->deserialize(s);

        REQUIRE(sceneObject->getTransform() == Transform());
    }
}