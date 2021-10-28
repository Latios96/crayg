//
// Created by Jan on 28.10.2021.
//


#include <catch2/catch.hpp>
#include <pxr/base/gf/matrix4d.h>
#include <Conversions.h>

namespace crayg {

TEST_CASE("ConvertMatrix4d") {

    SECTION("should convert identy matrix") {
        pxr::GfMatrix4d matrix;
        matrix.SetIdentity();

        const Matrix4x4f convertedMatrix = Conversions::convert(matrix);

        REQUIRE(convertedMatrix == Matrix4x4f());
    }
}

}