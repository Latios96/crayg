//
// Created by Jan on 28.10.2021.
//


#include <catch2/catch.hpp>
#include <pxr/base/gf/matrix4d.h>
#include <Conversions.h>

namespace crayg {

TEST_CASE("ConvertMatrix4d") {

    SECTION("should convert identity matrix") {
        pxr::GfMatrix4d matrix {};
        matrix.SetIdentity();
        Matrix4x4f expectedMatrix(1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1);

        const Matrix4x4f convertedMatrix = Conversions::convert(matrix);

        REQUIRE(convertedMatrix == expectedMatrix);
    }

    SECTION("should convert translated matrix") {
        pxr::GfMatrix4d matrix {};
        matrix.SetIdentity();
        matrix.SetTranslate({1, 2, 3});
        Matrix4x4f expectedMatrix(1, 0, 0, 1,
                                  0, 1, 0, 2,
                                  0, 0, 1, -3,
                                  0, 0, 0, 1);

        const Matrix4x4f convertedMatrix = Conversions::convert(matrix);

        REQUIRE(convertedMatrix == expectedMatrix);
    }
}

TEST_CASE("ConvertVec3f") {
    SECTION("should convert Vec3f") {
        const pxr::GfVec3f vectorToConvert(1, 2, 3);

        const Vector3f convertedVector = Conversions::convert(vectorToConvert);

        REQUIRE(convertedVector == Vector3f(1, 2, 3));
    }
}

}