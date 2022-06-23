#include <catch2/catch.hpp>
#include "scene/trianglemesh/TriangleMesh.h"
#include "scene/trianglemesh/primvars/TriangleMeshPerPointPrimVar.h"
#include "fixtures/TriangleMeshFixtures.h"

namespace crayg {

TEST_CASE("TriangleMeshPerPointPrimVar::interpolateAt")
{
    // TODO use a fixture
    TriangleMesh triangleMesh;
    triangleMesh.points = std::vector<Vector3f>({{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}});
    triangleMesh.faceVertexIndices = std::vector<TriangleMesh::FaceVertexIndices>({{0, 2, 1}, {2, 3, 1}});

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

    SECTION("should return the correct interpolated value for a point shared by multiple faces") {
        auto testData = GENERATE(table<int, Vector3f, Color>({{1, {0.0f, 0, 1.0f}, Color::createWhite()},
                                                              {2, {0.0f, 0.0f, 1.0f}, Color::createWhite()},
                                                              {0, {0.0f, 0.0f, 0.0f}, Color::createBlack()},
                                                              {3, {0.0f, 0.0f, 2.0f}, Color::createBlack()}}));

        TriangleMesh triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();
        TriangleMeshPerPointPrimVar<Color> primVar(triangleMesh);
        primVar.allocate();
        primVar.write(1, Color::createWhite());

        Color interpolatedValueForFace1 = primVar.interpolateAt(std::get<0>(testData), std::get<1>(testData));

        REQUIRE(interpolatedValueForFace1 == std::get<2>(testData));
    }

}

TEST_CASE("TriangleMeshPerPointPrimVar::==") {
    // TODO use a fixture
    TriangleMesh triangleMesh;
    triangleMesh.points = std::vector<Vector3f>({{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}});
    triangleMesh.faceVertexIndices = std::vector<TriangleMesh::FaceVertexIndices>({{0, 2, 1}, {2, 3, 1}});

    TriangleMeshPerPointPrimVar<Color> primVar(triangleMesh);
    primVar.allocate();
    primVar.write(0, Color(1, 0, 0));
    primVar.write(1, Color(0, 1, 0));
    primVar.write(2, Color(0, 0, 1));
    primVar.write(3, Color(1, 0, 0));

    SECTION("primvar should be equal to equivalent buffer") {
        REQUIRE(primVar == std::vector<Color>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 0, 0}}));
    }

    SECTION("primvar should not be equal to different equivalent buffer") {
        REQUIRE(primVar != std::vector<Color>());
    }
}

}