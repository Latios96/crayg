//
// Created by jan on 29.12.18.
//

#include <catch2/catch.hpp>
#include <fakeit.hpp>
using namespace fakeit;
#include <sceneIO/write/Serializer.h>
#include <scene/GroundPlane.h>

namespace crayg {

TEST_CASE("GroundPlaneSerialization") {

    GroundPlane myGroundPlane;

    SECTION("serialize") {
        fakeit::Mock<Serializer> mockSerializer;
        fakeit::When(Method(mockSerializer, writeVector3f)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeType)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeMatrix4x4f)).AlwaysReturn();

        Serializer &s = mockSerializer.get();
        myGroundPlane.serialize(s);

        fakeit::Verify(Method(mockSerializer, writeMatrix4x4f).Using("transform", Matrix4x4f()));
        fakeit::Verify(Method(mockSerializer, writeType).Using("GroundPlane"));
    }

    SECTION("deserialize") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, hasProperty).Using("position")).Return(true);
        When(Method(mockDeserializer, readVector3f).Using("position")).Return(Vector3f(1, 2, 3));

        Deserializer &s = mockDeserializer.get();
        myGroundPlane.deserialize(s);

        REQUIRE(myGroundPlane.getPosition() == Vector3f(1, 2, 3));
    }
}

TEST_CASE("GroundPlaneIntersection") {

    std::shared_ptr<GroundPlane> myGroundPlane = std::make_shared<GroundPlane>();

    Ray NOT_PARALLEL_RAY({0, 1, 0}, {0, -1, -1});
    Ray PARALLEL_RAY({0, 1, 0}, {0, 0, -1});

    SECTION("NotParallelRayIsIntersecting") {
        REQUIRE(myGroundPlane->isIntersecting(NOT_PARALLEL_RAY));
    }

    SECTION("ParallelRayIsNotIntersecting") {
        REQUIRE_FALSE(myGroundPlane->isIntersecting(PARALLEL_RAY));
    }

    SECTION("NotParallelRayReturnsCorrectIntersection") {
        Imageable::Intersection intersection = myGroundPlane->intersect(NOT_PARALLEL_RAY);
        REQUIRE(intersection.imageable == myGroundPlane);
        REQUIRE(intersection.rayParameter == 1.0f);
    }SECTION("ParallelRayReturnsInvalidIntersection") {
        Imageable::Intersection intersection = myGroundPlane->intersect(PARALLEL_RAY);
        REQUIRE_FALSE(intersection.isValid());
    }
}

}