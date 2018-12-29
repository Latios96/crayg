//
// Created by jan on 29.12.18.
//
#include <catch.hpp>
#include <fakeit.hpp>
#include <foundation/Vector3f.h>
#include <scene/Camera.h>

using namespace fakeit;

TEST_CASE("CameraSerialization"){
    Vector3f CAMERA_POSITION(1,2,3);
    Vector3f CAMERA_USER_UP_VECTOR(0,1,0);
    Vector3f CAMERA_CENTER_OF_INTEREST(0,0,-1);
    float CAMERA_FOCAL_LENGTH = 50.0f;
    float CAMERA_FILMBACK_SIZE = 35.0f;

    Camera myCamera(CAMERA_POSITION,
            CAMERA_USER_UP_VECTOR,
            CAMERA_CENTER_OF_INTEREST,
            CAMERA_FOCAL_LENGTH,
            CAMERA_FILMBACK_SIZE);

    SECTION("serialize"){
        fakeit::Mock<Serializer> mockSerializer;
        fakeit::When(Method(mockSerializer,writeVector3f)).AlwaysReturn();
        fakeit::When(Method(mockSerializer,writeFloat)).AlwaysReturn();
        fakeit::When(Method(mockSerializer,writeType)).AlwaysReturn();

        Serializer &s = mockSerializer.get();
        myCamera.serialize(s);

        fakeit::Verify(Method(mockSerializer,writeVector3f).Using("position", CAMERA_POSITION));
        fakeit::Verify(Method(mockSerializer,writeVector3f).Using("userUpVector", CAMERA_USER_UP_VECTOR));
        fakeit::Verify(Method(mockSerializer,writeVector3f).Using("centerOfInterest", CAMERA_CENTER_OF_INTEREST));
        fakeit::Verify(Method(mockSerializer,writeFloat).Using("focalLength", CAMERA_FOCAL_LENGTH));
        fakeit::Verify(Method(mockSerializer,writeFloat).Using("filmbackSize", CAMERA_FILMBACK_SIZE));
        fakeit::Verify(Method(mockSerializer,writeType).Using("Camera"));
    }

    SECTION("deserialize"){
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer,readVector3f).Using("position")).Return(CAMERA_POSITION);
        When(Method(mockDeserializer,readVector3f).Using("userUpVector")).Return(CAMERA_USER_UP_VECTOR);
        When(Method(mockDeserializer,readVector3f).Using("centerOfInterest")).Return(CAMERA_CENTER_OF_INTEREST);
        When(Method(mockDeserializer,readFloat).Using("focalLength")).Return(CAMERA_FOCAL_LENGTH);
        When(Method(mockDeserializer,readFloat).Using("filmbackSize")).Return(CAMERA_FILMBACK_SIZE);

        Deserializer &s = mockDeserializer.get();
        myCamera.deserialize(s);

        REQUIRE(myCamera.getPosition() == CAMERA_POSITION);
        REQUIRE(myCamera.getUserUpVector() == CAMERA_USER_UP_VECTOR);
        REQUIRE(myCamera.getCenterOfInterest() == CAMERA_CENTER_OF_INTEREST);
        REQUIRE((myCamera.getFocalLength() == CAMERA_FOCAL_LENGTH));
        REQUIRE(myCamera.getFilmbackSize() == CAMERA_FILMBACK_SIZE);
    }
}