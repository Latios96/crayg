#include "crayg/scene/io/write/usd/UsdSceneWriter.h"
#include "crayg/scene/primitives/subdivisionsurfacemesh/FanTriangulator.h"
#include "crayg/scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "fixtures/SubdivisionSurfaceMeshFixtures.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("FanTriangulator::fanTriangulate") {

    SECTION("should triangulate empty correctly") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        std::vector<TriangleMesh::FaceVertexIndices> target;
        FanTriangulator fanTriangulator(subdivisionSurfaceMesh);

        fanTriangulator.fanTriangulate(target);

        REQUIRE(target.empty());
    }

    SECTION("should triangulate quad plane correctly") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);
        std::vector<TriangleMesh::FaceVertexIndices> target;
        FanTriangulator fanTriangulator(subdivisionSurfaceMesh);

        fanTriangulator.fanTriangulate(target);

        REQUIRE(target == std::vector<TriangleMesh::FaceVertexIndices>({{0, 1, 2}, {0, 2, 3}}));
    }

    SECTION("should triangulate triangle plane correctly") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        SubdivisionSurfaceMeshFixtures::createTriangleUnitPlane(subdivisionSurfaceMesh);
        std::vector<TriangleMesh::FaceVertexIndices> target;
        FanTriangulator fanTriangulator(subdivisionSurfaceMesh);

        fanTriangulator.fanTriangulate(target);

        REQUIRE(target == std::vector<TriangleMesh::FaceVertexIndices>({{0, 1, 2}, {0, 2, 3}}));
    }

    SECTION("should triangulate quad cube correctly") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        SubdivisionSurfaceMeshFixtures::createUnitCube(subdivisionSurfaceMesh);
        std::vector<TriangleMesh::FaceVertexIndices> target;
        FanTriangulator fanTriangulator(subdivisionSurfaceMesh);

        fanTriangulator.fanTriangulate(target);

        REQUIRE(target == std::vector<TriangleMesh::FaceVertexIndices>({{0, 1, 3},
                                                                        {0, 3, 2},
                                                                        {2, 3, 5},
                                                                        {2, 5, 4},
                                                                        {4, 5, 7},
                                                                        {4, 7, 6},
                                                                        {6, 7, 1},
                                                                        {6, 1, 0},
                                                                        {1, 7, 5},
                                                                        {1, 5, 3},
                                                                        {6, 0, 2},
                                                                        {6, 2, 4}}));
    }
}

}