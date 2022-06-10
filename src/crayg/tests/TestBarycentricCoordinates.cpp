#include <catch2/catch.hpp>
#include <basics/BarycentricCoordinates.h>
#include <scene/TriangleMesh.h>

namespace crayg {

TEST_CASE("BarycentricCoordinates::construct") {
    TriangleMesh triangleMesh;
    triangleMesh.points.emplace_back(0, 0, 0);
    triangleMesh.points.emplace_back(0, 1, 0);
    triangleMesh.points.emplace_back(1, 0, 0);
    triangleMesh.faceIndices.push_back(0);
    triangleMesh.faceIndices.push_back(1);
    triangleMesh.faceIndices.push_back(2);
    triangleMesh.beforeRender();

    Triangle triangle(&triangleMesh, 0);

    SECTION("should construct correctly from triangle") {
        BarycentricCoordinates coordinates(triangle, {0.25, 0.25, 0.25});

        REQUIRE(coordinates == BarycentricCoordinates(0.5, 0.25, 0.25));
    }

    SECTION("should construct correctly from scalars") {
        BarycentricCoordinates coordinates({0, 0, 0}, {0, 1, 0}, {1, 0, 0}, triangle.getNormal(), {0.25, 0.25, 0.25});

        REQUIRE(coordinates == BarycentricCoordinates(0.5, 0.25, 0.25));
    }
}

TEST_CASE("BarycentricCoordinates::interpolate") {
    SECTION("should interpolate constant value correctly") {
        BarycentricCoordinates coordinates({0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, -1}, {0.25, 0.25, 0.25});

        Color interpolatedColor =
            coordinates.interpolateLinear(Color::createGrey(0.5f), Color::createGrey(0.5f), Color::createGrey(0.5f));

        REQUIRE(interpolatedColor == Color::createGrey(0.5f));
    }

    SECTION("should interpolate values correctly") {
        BarycentricCoordinates coordinates({0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, -1}, {0.25, 0.25, 0.25});

        Color interpolatedColor = coordinates.interpolateLinear(Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1));

        REQUIRE(interpolatedColor == Color(0.5f, 0.25f, 0.25f));
    }
}

}