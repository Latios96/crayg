#include <basics/Transform.h>
#include <basics/Vector3f.h>
#include <catch2/catch.hpp>

namespace crayg {

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
        // clang-format off
        Transform expectedTransform = Transform(Matrix4x4f(0.81f, -0.46f, 0.34f, 0.f,
                                                           0.54f, 0.83f, -0.16f, 0.f,
                                                           -0.20f, 0.31f, 0.925f, 0.f,
                                                           0.f, 0.f, 0.f, 1.f));
        // clang-format on

        REQUIRE(transform.matrix.isEqualTo(expectedTransform.matrix, 0.01f));
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

TEST_CASE("apply transform to Normal", "[Transform]") {
    SECTION("apply identiy matrix should not change") {
        Vector3f vector3f(1, 2, 3);
        Transform transform;

        REQUIRE(transform.applyForNormal(vector3f) == vector3f);
    }

    SECTION("should not transform because translate only") {
        Vector3f vector3f(1, 2, 3);
        Transform transform = Transform::withPosition({3, 0, 0});

        const Vector3f &f = transform.applyForNormal(vector3f);
        REQUIRE(f == vector3f);
    }

    SECTION("should transform") {
        Vector3f vector3f(0, 1, 0);
        Transform transform = Transform::withRotation(90, 0, 0);

        REQUIRE(transform.applyForNormal(vector3f) == Vector3f(0, 0, 1));
    }
}

}
