//
// Created by Jan Honsbrok on 06.11.18.
//
#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <sceneIO/Serializable.h>
#include <scene/Scene.h>
#include "scene/RectLight.h"
#include "intersectors/SceneIntersector.h"

using namespace fakeit;

namespace crayg {

TEST_CASE("serialize RectLight", "[RectLight]") {
    RectLight myLight(Transform::withPosition({1, 2, 3}), 3.0f, 1, 1);

    fakeit::Mock<Serializer> mockSerializer;
    fakeit::When(Method(mockSerializer, writeFloat)).AlwaysReturn();
    fakeit::When(Method(mockSerializer, writeMatrix4x4f)).AlwaysReturn();
    fakeit::When(Method(mockSerializer, writeType)).AlwaysReturn();

    Serializer &s = mockSerializer.get();
    myLight.serialize(s);

    fakeit::Verify(Method(mockSerializer, writeFloat).Using("intensity", 3.0f));
    fakeit::Verify(Method(mockSerializer, writeMatrix4x4f).Using("transform",
                                                                 Transform::withPosition({1, 2, 3}).matrix));
    fakeit::Verify(Method(mockSerializer, writeType).Using("RectLight"));
}

TEST_CASE("deserialize RectLight", "[RectLight]") {

    auto sceneObject = std::make_shared<RectLight>();

    SECTION("scene containing position should be converted to transform") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, hasProperty).Using("position")).Return(true);
        When(Method(mockDeserializer, readVector3f).Using("position")).Return(Vector3f(1, 2, 3));
        When(Method(mockDeserializer, readMatrix4x4f).Using("transform")).Return(Matrix4x4f());
        When(Method(mockDeserializer, readFloat).Using("intensity")).Return(1);
        When(Method(mockDeserializer, readFloat).Using("width")).Return(2);
        When(Method(mockDeserializer, readFloat).Using("height")).Return(3);

        Deserializer &s = mockDeserializer.get();
        sceneObject->deserialize(s);

        REQUIRE(sceneObject->getTransform() == Transform::withPosition({1, 2, 3}));
    }

    SECTION("scene containing transform should be read correctly") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, hasProperty).Using("position")).Return(false);
        When(Method(mockDeserializer, readMatrix4x4f).Using("transform")).Return(Matrix4x4f());
        When(Method(mockDeserializer, readFloat).Using("intensity")).Return(1);
        When(Method(mockDeserializer, readFloat).Using("width")).Return(2);
        When(Method(mockDeserializer, readFloat).Using("height")).Return(3);

        Deserializer &s = mockDeserializer.get();
        sceneObject->deserialize(s);

        REQUIRE(sceneObject->getTransform() == Transform());
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

TEST_CASE("RectLight::sampleLightShape") {

    AreaLightFixture areaLightFixture;

    SECTION("sampleLightShape should respect width and height") {
        const float realWidth = 1;
        const float realHeight = 1;

        for (int i = 0; i < 1000; i++) {
            const Vector3f samplePoint = areaLightFixture.areaLight->sampleLightShape();
            REQUIRE(samplePoint.x < (areaLightFixture.position.x + realWidth / 2));
            REQUIRE(samplePoint.x > (areaLightFixture.position.x - realWidth / 2));
            REQUIRE(samplePoint.y < (areaLightFixture.position.y + realHeight / 2));
            REQUIRE(samplePoint.y > (areaLightFixture.position.y - realHeight / 2));
            REQUIRE(samplePoint.z == areaLightFixture.position.z);
        }
    }

    SECTION("sampleLightShape should respect scale") {
        areaLightFixture.areaLight->setWidth(5);
        areaLightFixture.areaLight->setHeight(5);
        const Transform transform =
            Transform(Transform::withPosition(areaLightFixture.position).matrix
                          * Transform::withScale(1. / 5, 1. / 5, 1. / 5).matrix);
        areaLightFixture.areaLight->setTransform(transform);
        const float realWidth = 1;
        const float realHeight = 1;

        for (int i = 0; i < 1000; i++) {
            const Vector3f samplePoint = areaLightFixture.areaLight->sampleLightShape();
            REQUIRE(samplePoint.x < (areaLightFixture.position.x + realWidth / 2));
            REQUIRE(samplePoint.x > (areaLightFixture.position.x - realWidth / 2));
            REQUIRE(samplePoint.y < (areaLightFixture.position.y + realHeight / 2));
            REQUIRE(samplePoint.y > (areaLightFixture.position.y - realHeight / 2));
            REQUIRE(samplePoint.z == areaLightFixture.position.z);
        }
    }
}

}

