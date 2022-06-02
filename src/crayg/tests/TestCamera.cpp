//
// Created by jan on 29.12.18.
//
#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <basics/Vector3f.h>
#include <scene/Camera.h>

using namespace fakeit;

namespace crayg {

TEST_CASE("CameraSerialization") {
    Transform CAMERA_TRANSFORM = Transform::withPosition({1, 2, 3});
    Vector3f CAMERA_USER_UP_VECTOR(0, 1, 0);
    Vector3f CAMERA_CENTER_OF_INTEREST(1, 2, 4);
    float CAMERA_FOCAL_LENGTH = 50.0f;
    float CAMERA_FILMBACK_SIZE = 35.0f;

    Camera myCamera(CAMERA_TRANSFORM,
                    CAMERA_FOCAL_LENGTH,
                    CAMERA_FILMBACK_SIZE);

    SECTION("serialize") {
        fakeit::Mock<Serializer> mockSerializer;
        fakeit::When(Method(mockSerializer, writeMatrix4x4f)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeFloat)).AlwaysReturn();
        fakeit::When(Method(mockSerializer, writeType)).AlwaysReturn();

        Serializer &s = mockSerializer.get();
        myCamera.serialize(s);

        fakeit::Verify(Method(mockSerializer, writeMatrix4x4f).Using("transform", CAMERA_TRANSFORM.matrix));
        fakeit::Verify(Method(mockSerializer, writeFloat).Using("focalLength", CAMERA_FOCAL_LENGTH));
        fakeit::Verify(Method(mockSerializer, writeFloat).Using("filmbackSize", CAMERA_FILMBACK_SIZE));
        fakeit::Verify(Method(mockSerializer, writeType).Using("Camera"));
    }

    SECTION("deserialize") {
        fakeit::Mock<Deserializer> mockDeserializer;
        When(Method(mockDeserializer, readMatrix4x4f).Using("transform")).Return(CAMERA_TRANSFORM.matrix);
        When(Method(mockDeserializer, readFloat).Using("focalLength")).Return(CAMERA_FOCAL_LENGTH);
        When(Method(mockDeserializer, readFloat).Using("filmbackSize")).Return(CAMERA_FILMBACK_SIZE);

        Deserializer &s = mockDeserializer.get();
        myCamera.deserialize(s);

        REQUIRE(myCamera.getTransform() == CAMERA_TRANSFORM);
        REQUIRE(myCamera.getUserUpVector() == CAMERA_USER_UP_VECTOR);
        REQUIRE(myCamera.getCenterOfInterest() == CAMERA_CENTER_OF_INTEREST);
        REQUIRE((myCamera.getFocalLength() == CAMERA_FOCAL_LENGTH));
        REQUIRE(myCamera.getFilmbackSize() == CAMERA_FILMBACK_SIZE);
    }
}

TEST_CASE("field of view") {
    SECTION("get horizontal field of view") {
        float focalLength = 36;
        float filmbackSize = 36.0f;
        Camera camera(Transform(), focalLength, filmbackSize);

        const float horizontalFieldOfViewInRadians = camera.getHorizontalFieldOfView();

        REQUIRE(horizontalFieldOfViewInRadians == Catch::Detail::Approx(0.92729343));
    }
}

}