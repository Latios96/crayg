#include <catch2/catch.hpp>
#include "scene/TriangleMesh.h"
#include "scene/TriangleMeshPerPointPrimVar.h"

namespace crayg {

TEST_CASE("TriangleMeshPerPointPrimVar::interpolateAt")
{
    TriangleMesh triangleMesh;
    triangleMesh.points = std::vector<Vector3f>({{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}});
    triangleMesh.faceIndices = std::vector<int>({0, 2, 1, 2, 3, 1});

    SECTION("should interpolate constant value correctly") {
        TriangleMeshPerPointPrimVar<Color> primVar(triangleMesh);
        primVar.allocate();
        primVar.write(0, Color::createGrey(0.5));
        primVar.write(1, Color::createGrey(0.5));
        primVar.write(2, Color::createGrey(0.5));
        primVar.write(3, Color::createGrey(0.5));

        Color interpolatedValue = primVar.interpolateAt(0, {-0.25, 0, 0.25});

        REQUIRE(interpolatedValue == Color::createGrey(0.5));
    }

    SECTION("should interpolate non-constant value correctly") {
        TriangleMeshPerPointPrimVar<Color> primVar(triangleMesh);
        primVar.allocate();
        primVar.write(0, Color(1, 0, 0));
        primVar.write(1, Color(0, 1, 0));
        primVar.write(2, Color(0, 0, 1));
        primVar.write(3, Color(1, 0, 0));

        Color interpolatedValue = primVar.interpolateAt(0, {-0.25, 0, 0.25});

        REQUIRE(interpolatedValue == Color(0.5f, 0.25f, 0.25f));
    }

}

}