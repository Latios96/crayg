//
// Created by Jan on 09.11.2020.
//
#include <catch2/catch.hpp>
#include <basics/Matrix4x4f.h>
#include <sstream>

TEST_CASE("construction", "[Matrix4x4f]") {

    SECTION("default constructor should create identity matrix") {
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

    SECTION("construct from params") {
        Matrix4x4f matrix4X4F(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        REQUIRE(matrix4X4F.values[0][0] == 1);
        REQUIRE(matrix4X4F.values[1][0] == 2);
        REQUIRE(matrix4X4F.values[2][0] == 3);
        REQUIRE(matrix4X4F.values[3][0] == 4);
        REQUIRE(matrix4X4F.values[0][1] == 5);
        REQUIRE(matrix4X4F.values[1][1] == 6);
        REQUIRE(matrix4X4F.values[2][1] == 7);
        REQUIRE(matrix4X4F.values[3][1] == 8);
        REQUIRE(matrix4X4F.values[0][2] == 9);
        REQUIRE(matrix4X4F.values[1][2] == 10);
        REQUIRE(matrix4X4F.values[2][2] == 11);
        REQUIRE(matrix4X4F.values[3][2] == 12);
        REQUIRE(matrix4X4F.values[0][3] == 13);
        REQUIRE(matrix4X4F.values[1][3] == 14);
        REQUIRE(matrix4X4F.values[2][3] == 15);
        REQUIRE(matrix4X4F.values[3][3] == 16);
    }
}

TEST_CASE("outstream", "[Matrix4x4f]") {
    Matrix4x4f matrix4X4F;
    std::stringstream ss;
    ss << matrix4X4F;
    REQUIRE("Matrix4x4f(values={1.0 0.0 0.0 0.0, 0.0 1.0 0.0 0.0, 0.0 0.0 1.0 0.0, 0.0 0.0 0.0 1.0})" == ss.str());
}

// equal
// outstream
// format for spdlog
