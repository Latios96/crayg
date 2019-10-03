//
// Created by Jan Honsbrok on 06.11.18.
//
#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <sceneIO/Serializable.h>
#include "scene/Light.h"

TEST_CASE("Light") {
    Light myLight;
    myLight.setPosition(Vector3f(1, 2, 3));
    myLight.setIntensity(3.0f);

    SECTION("serialize") {
        fakeit::Mock<Serializer> mockSerializer;
        fakeit::When(Method(mockSerializer, writeFloat)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeVector3f)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeType)).AlwaysReturn();

        Serializer &s = mockSerializer.get();
        myLight.serialize(s);

        fakeit::Verify(Method(mockSerializer, writeFloat).Using("intensity", 3.0f));
        fakeit::Verify(Method(mockSerializer, writeVector3f).Using("position", Vector3f(1, 2, 3)));
        fakeit::Verify(Method(mockSerializer, writeType).Using("Light"));
    }

    SECTION("deserialize") {
        fakeit::Mock<Deserializer> mockDeserializer;
        fakeit::When(Method(mockDeserializer, readFloat).Using("intensity")).Return(3.0f);
        fakeit::When(Method(mockDeserializer, readVector3f).Using("position")).Return(Vector3f(1, 2, 3));

        Deserializer &s = mockDeserializer.get();
        myLight.deserialize(s);

        REQUIRE(myLight.getPosition() == Vector3f(1, 2, 3));
        REQUIRE(myLight.getIntensity() == 3.0f);
    }
}
