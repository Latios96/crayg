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

    SECTION("should create with position") {
        Transform transform = Transform::withPosition({1, 2, 3});

        REQUIRE(transform.apply({1, 2, 3}) == Vector3f(2, 4, 6));
    }

    SECTION("should create with rotation") {
        Transform transform = Transform::withRotation(10, 20, 30);

        Transform expectedTransform = Transform(Matrix4x4f(0.81, -0.46, 0.34, 0,
                                                           0.54, 0.83, -0.16, 0,
                                                           -0.20, 0.31, 0.925, 0,
                                                           0, 0, 0, 1));

        REQUIRE(transform.matrix.isEqualTo(expectedTransform.matrix, 0.01));
    }

    SECTION("should create with scale") {
        Transform transform = Transform::withScale(2, 3, 4);

        REQUIRE(transform.apply({1, 2, 3}) == Vector3f(2, 6, 12));
    }

    SECTION("should copy") {
        Transform transform = Transform::withPosition({1, 2, 3});

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

TEST_CASE("apply transform to Ray", "[Transform]") {
    SECTION("apply identiy matrix should not change") {
        Ray ray({1, 2, 3}, {4, 5, 6});
        Transform transform;

        REQUIRE(transform.apply(ray) == ray);
    }

    SECTION("should transform") {
        Ray ray({1, 2, 3}, {4, 5, 6});
        Transform transform = Transform::withPosition({1, 2, 3});

        REQUIRE(transform.apply(ray) == Ray({2, 4, 6}, {5, 7, 9}));
    }
}


