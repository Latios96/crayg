//
// Created by Jan on 09.11.2020.
//
#include <catch2/catch.hpp>
#include <basics/Vector3f.h>
#include <basics/Transform.h>

TEST_CASE("Transform Construction", "[Transform]") {
    SECTION("should construct identy matrix") {
        Transform transform;

        REQUIRE(transform.matrix == Matrix4x4f());
    }

    SECTION("should create from position") {
        Transform transform = Transform::fromPosition({1, 2, 3});

        REQUIRE(transform.apply({1, 2, 3}) == Vector3f(2, 4, 6));
    }

    SECTION("should copy") {
        Transform transform = Transform::fromPosition({1, 2, 3});

        Transform copy = transform;

        REQUIRE(copy == transform);
    }
}

TEST_CASE("apply transform to vector", "[Transform]") {
    SECTION("apply identiy matrix should not change") {
        Vector3f vector3f(1, 2, 3);
        Transform transform;

        REQUIRE(transform.apply(vector3f) == vector3f);
    }

    SECTION("should transform vector on x axis") {
        Vector3f vector3f(1, 2, 3);
        Matrix4x4f matrix4X4f(1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
        Transform transform(matrix4X4f);

        const Vector3f &f = transform.apply(vector3f);
        REQUIRE(f == Vector3f(2, 2, 3));
    }

    SECTION("should transform vector on y axis") {
        Vector3f vector3f(1, 2, 3);
        Matrix4x4f matrix4X4f(1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1);
        Transform transform(matrix4X4f);

        const Vector3f &f = transform.apply(vector3f);
        REQUIRE(f == Vector3f(1, 3, 3));
    }

    SECTION("should transform vector on z axis") {
        Vector3f vector3f(1, 2, 3);
        Matrix4x4f matrix4X4f(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1);
        Transform transform(matrix4X4f);

        const Vector3f &f = transform.apply(vector3f);
        REQUIRE(f == Vector3f(1, 2, 4));
    }
}
TEST_CASE("transform to position", "[Transform]") {
    const Vector3f position = Vector3f(1, 2, 3);

    Transform transform = Transform::fromPosition(position);

    REQUIRE(transform.toPosition() == position);
}
