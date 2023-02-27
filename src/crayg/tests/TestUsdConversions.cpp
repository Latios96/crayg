#include "sceneIO/usd/UsdConversions.h"
#include <catch2/catch.hpp>
#include <pxr/base/gf/matrix4d.h>

namespace crayg {

TEST_CASE("ConvertGfMatrix4d") {

    SECTION("should convert identity matrix") {
        pxr::GfMatrix4d matrix{};
        matrix.SetIdentity();
        // clang-format off
        Matrix4x4f expectedMatrix(1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1);
        // clang-format on

        const Matrix4x4f convertedMatrix = UsdConversions::convert(matrix);

        REQUIRE(convertedMatrix == expectedMatrix);
    }

    SECTION("should convert translated matrix") {
        pxr::GfMatrix4d matrix{};
        matrix.SetIdentity();
        matrix.SetTranslate({1, 2, 3});
        // clang-format off
        Matrix4x4f expectedMatrix(1, 0, 0, 1,
                                  0, 1, 0, 2,
                                  0, 0, 1, -3,
                                  0, 0, 0, 1);
        // clang-format on

        const Matrix4x4f convertedMatrix = UsdConversions::convert(matrix);

        REQUIRE(convertedMatrix == expectedMatrix);
    }
}

TEST_CASE("ConvertMatrix4d") {

    SECTION("should convert identity matrix") {
        // clang-format off
        Matrix4x4f matrix(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
        // clang-format on
        pxr::GfMatrix4d expectedMatrix{};
        expectedMatrix.SetIdentity();

        const pxr::GfMatrix4d convertedMatrix = UsdConversions::convert(matrix);

        REQUIRE(convertedMatrix == expectedMatrix);
    }

    SECTION("should convert translated matrix") {
        // clang-format off
        Matrix4x4f matrix(1, 0, 0, 1,
                          0, 1, 0, 2,
                          0, 0, 1, -3,
                          0, 0, 0, 1);
        // clang-format on
        pxr::GfMatrix4d expectedMatrix{};
        expectedMatrix.SetIdentity();
        expectedMatrix.SetTranslate({1, 2, 3});

        const pxr::GfMatrix4d convertedMatrix = UsdConversions::convert(matrix);

        REQUIRE(convertedMatrix == expectedMatrix);
    }
}

TEST_CASE("ConvertVec3f") {
    SECTION("should convert Vec3f") {
        const pxr::GfVec3f vectorToConvert(1, 2, 3);

        const Vector3f convertedVector = UsdConversions::convert(vectorToConvert);

        REQUIRE(convertedVector == Vector3f(1, 2, -3));
    }

    SECTION("should convert Vec3d") {
        const pxr::GfVec3d vectorToConvert(1, 2, 3);

        const Vector3f convertedVector = UsdConversions::convert(vectorToConvert);

        REQUIRE(convertedVector == Vector3f(1, 2, -3));
    }
}

TEST_CASE("convertColor") {
    SECTION("should convert Vec3f to Color") {
        const pxr::GfVec3f colorToConvert(1, 2, 3);

        const Color convertedColor = UsdConversions::convertColor(colorToConvert);

        REQUIRE(convertedColor == Color(1, 2, 3));
    }
}

}