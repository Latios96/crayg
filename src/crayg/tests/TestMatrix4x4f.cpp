//
// Created by Jan on 09.11.2020.
//
#include <catch2/catch.hpp>
#include <basics/Matrix4x4f.h>
#include <sstream>

TEST_CASE("construct Matrix4x4f", "[Matrix4x4f]") {

    SECTION("default constructor should create identity matrix") {
        Matrix4x4f matrix4X4F;

        REQUIRE(matrix4X4F.values[0][0] == 1);
        REQUIRE(matrix4X4F.values[0][1] == 0);
        REQUIRE(matrix4X4F.values[0][2] == 0);
        REQUIRE(matrix4X4F.values[0][3] == 0);
        REQUIRE(matrix4X4F.values[1][0] == 0);
        REQUIRE(matrix4X4F.values[1][1] == 1);
        REQUIRE(matrix4X4F.values[1][2] == 0);
        REQUIRE(matrix4X4F.values[1][3] == 0);
        REQUIRE(matrix4X4F.values[2][0] == 0);
        REQUIRE(matrix4X4F.values[2][1] == 0);
        REQUIRE(matrix4X4F.values[2][2] == 1);
        REQUIRE(matrix4X4F.values[2][3] == 0);
        REQUIRE(matrix4X4F.values[3][0] == 0);
        REQUIRE(matrix4X4F.values[3][1] == 0);
        REQUIRE(matrix4X4F.values[3][2] == 0);
        REQUIRE(matrix4X4F.values[3][3] == 1);
    }

    SECTION("construct from params") {
        Matrix4x4f matrix4X4F(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        REQUIRE(matrix4X4F.values[0][0] == 1);
        REQUIRE(matrix4X4F.values[0][1] == 2);
        REQUIRE(matrix4X4F.values[0][2] == 3);
        REQUIRE(matrix4X4F.values[0][3] == 4);
        REQUIRE(matrix4X4F.values[1][0] == 5);
        REQUIRE(matrix4X4F.values[1][1] == 6);
        REQUIRE(matrix4X4F.values[1][2] == 7);
        REQUIRE(matrix4X4F.values[1][3] == 8);
        REQUIRE(matrix4X4F.values[2][0] == 9);
        REQUIRE(matrix4X4F.values[2][1] == 10);
        REQUIRE(matrix4X4F.values[2][2] == 11);
        REQUIRE(matrix4X4F.values[2][3] == 12);
        REQUIRE(matrix4X4F.values[3][0] == 13);
        REQUIRE(matrix4X4F.values[3][1] == 14);
        REQUIRE(matrix4X4F.values[3][2] == 15);
        REQUIRE(matrix4X4F.values[3][3] == 16);
    }

    SECTION("copy constructor") {
        Matrix4x4f matrix4X4F(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

        Matrix4x4f copy = matrix4X4F;

        REQUIRE(matrix4X4F == copy);
    }
}

TEST_CASE("outstream", "[Matrix4x4f]") {
    Matrix4x4f matrix4X4F;
    std::stringstream ss;
    ss << matrix4X4F;
    REQUIRE("Matrix4x4f(values={1.0 0.0 0.0 0.0, 0.0 1.0 0.0 0.0, 0.0 0.0 1.0 0.0, 0.0 0.0 0.0 1.0})" == ss.str());
}

TEST_CASE("multiply matrices", "[Matrix4x4f]") {
    Matrix4x4f matrix1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Matrix4x4f matrix2(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);

    Matrix4x4f result = matrix1 * matrix2;
    REQUIRE(result.values[0][0] == 250);
    REQUIRE(result.values[0][1] == 260);
    REQUIRE(result.values[0][2] == 270);
    REQUIRE(result.values[0][3] == 280);
    REQUIRE(result.values[1][0] == 618);
    REQUIRE(result.values[1][1] == 644);
    REQUIRE(result.values[1][2] == 670);
    REQUIRE(result.values[1][3] == 696);
    REQUIRE(result.values[2][0] == 986);
    REQUIRE(result.values[2][1] == 1028);
    REQUIRE(result.values[2][2] == 1070);
    REQUIRE(result.values[2][3] == 1112);
    REQUIRE(result.values[3][0] == 1354);
    REQUIRE(result.values[3][1] == 1412);
    REQUIRE(result.values[3][2] == 1470);
    REQUIRE(result.values[3][3] == 1528);
}

TEST_CASE("equal operator", "[Matrix4x4f]") {
    SECTION("should be equal") {
        Matrix4x4f m1;
        Matrix4x4f m2;

        REQUIRE(m1 == m2);
    }

    SECTION("should not be equal") {
        Matrix4x4f m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        Matrix4x4f m2(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);

        REQUIRE(m1 != m2);
    }
}



// equal
