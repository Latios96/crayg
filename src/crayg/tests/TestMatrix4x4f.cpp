//
// Created by Jan on 09.11.2020.
//
#include <catch2/catch.hpp>
#include <basics/Matrix4x4f.h>

TEST_CASE("construction", "[Matrix4x4f]"){

    SECTION("default constructor should create identity matrix"){
        Matrix4x4f matrix4X4F;

        REQUIRE(matrix4X4F.values[0][0] == 1);
        REQUIRE(matrix4X4F.values[1][0] == 0);
        REQUIRE(matrix4X4F.values[2][0] == 0);
        REQUIRE(matrix4X4F.values[3][0] == 0);
        REQUIRE(matrix4X4F.values[0][1] == 0);
        REQUIRE(matrix4X4F.values[1][1] == 1);
        REQUIRE(matrix4X4F.values[2][1] == 0);
        REQUIRE(matrix4X4F.values[3][1] == 0);
        REQUIRE(matrix4X4F.values[0][2] == 0);
        REQUIRE(matrix4X4F.values[1][2] == 0);
        REQUIRE(matrix4X4F.values[2][2] == 1);
        REQUIRE(matrix4X4F.values[3][2] == 0);
        REQUIRE(matrix4X4F.values[0][3] == 0);
        REQUIRE(matrix4X4F.values[1][3] == 0);
        REQUIRE(matrix4X4F.values[2][3] == 0);
        REQUIRE(matrix4X4F.values[3][3] == 1);
    }
}

// equal
// outstream
// format for spdlog
