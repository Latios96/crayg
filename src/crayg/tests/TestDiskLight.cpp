//
// Created by Jan on 21.11.2020.
//

#include <catch2/catch.hpp>
#include <scene/DiskLight.h>
#include <fakeit.hpp>

using namespace fakeit;
// serialize
// deserialize
// shadow factor
// intersect / isIntersecting

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