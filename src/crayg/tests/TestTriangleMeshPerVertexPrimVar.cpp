#include <catch2/catch.hpp>
#include "scene/trianglemesh/TriangleMesh.h"
#include "scene/trianglemesh/primvars/TriangleMeshPerVertexPrimVar.h"

namespace crayg {

TEST_CASE("TriangleMeshPerVertexPrimVar::interpolateAt")
{
    TriangleMesh triangleMesh;
    triangleMesh.points = std::vector<Vector3f>({{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}});
    triangleMesh.faceVertexIndices.emplace_back(0, 2, 1);
    triangleMesh.faceVertexIndices.emplace_back(2, 3, 1);

    SECTION("should interpolate constant value correctly") {
        TriangleMeshPerVertexPrimVar<Color> primVar(triangleMesh);
        primVar.allocate();
        primVar.write(0, VertexData(Color::createGrey(0.5)));
        primVar.write(1, VertexData(Color::createGrey(0.5)));

        Color interpolatedValue = primVar.interpolateAt(0, {-0.25, 0, 0.25});

        REQUIRE(interpolatedValue == Color::createGrey(0.5));
    }

    SECTION("should interpolate non-constant value correctly") {
        TriangleMeshPerVertexPrimVar<Color> primVar(triangleMesh);
        primVar.allocate();
        primVar.write(0, VertexData(Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1)));
        primVar.write(1, VertexData(Color(0, 0, 0), Color(0, 1, 0), Color(1, 0, 0)));

        Color interpolatedValue = primVar.interpolateAt(0, {-0.25, 0, 0.25});

        REQUIRE(interpolatedValue == Color(0.5f, 0.25f, 0.25f));
    }

}

}