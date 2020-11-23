//
// Created by Jan Honsbrok on 06.11.18.
//
#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <sceneIO/Serializable.h>
#include <scene/Scene.h>
#include "scene/AreaLight.h"
#include "intersectors/SceneIntersector.h"

using namespace fakeit;

namespace crayg {

TEST_CASE("serialize AreaLight", "[AreaLight]") {
    AreaLight myLight;
    myLight.setPosition(Vector3f(1, 2, 3));
    myLight.setIntensity(3.0f);

    fakeit::Mock<Serializer> mockSerializer;
    fakeit::When(Method(mockSerializer, writeFloat)).AlwaysReturn();
    fakeit::When(Method(mockSerializer, writeMatrix4x4f)).AlwaysReturn();
    fakeit::When(Method(mockSerializer, writeType)).AlwaysReturn();

    Serializer &s = mockSerializer.get();
    myLight.serialize(s);

    fakeit::Verify(Method(mockSerializer, writeFloat).Using("intensity", 3.0f));
    fakeit::Verify(Method(mockSerializer, writeMatrix4x4f).Using("transform",
                                                                 Transform::withPosition({1, 2, 3}).matrix));
    fakeit::Verify(Method(mockSerializer, writeType).Using("AreaLight"));
}

TEST_CASE("deserialize AreaLight", "[AreaLight]") {

    auto sceneObject = std::make_shared<AreaLight>();

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

}

