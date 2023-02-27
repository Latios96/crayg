#include "fixtures/SubdivisionSurfaceMeshFixtures.h"
#include "scene/primitives/subdivisionsurfacemesh/OpenSubdivRefiner.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("OpenSubdivRefiner::refine") {

    SECTION("should refine mesh") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);
        OpenSubdivRefiner openSubdivRefiner(subdivisionSurfaceMesh);

        openSubdivRefiner.refine(1);

        REQUIRE(subdivisionSurfaceMesh.points == std::vector<Vector3f>({{-0.375f, 0, -0.375f},
                                                                        {0.375f, 0, -0.375f},
                                                                        {0.375f, 0, 0.375f},
                                                                        {-0.375f, 0, 0.375f},
                                                                        {0, 0, 0},
                                                                        {0, 0, -0.5},
                                                                        {0.5, 0, 0},
                                                                        {0, 0, 0.5f},
                                                                        {-0.5f, 0, 0}}));
        REQUIRE(subdivisionSurfaceMesh.faceVertexIndices ==
                std::vector<int>({0, 5, 4, 8, 5, 1, 6, 4, 4, 6, 2, 7, 8, 4, 7, 3}));
        REQUIRE(subdivisionSurfaceMesh.faceVertexCounts == std::vector<int>({4, 4, 4, 4}));
        REQUIRE_FALSE(subdivisionSurfaceMesh.normals.empty());
    }

    SECTION("should refine mesh with boundary interpolation edge only") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);
        subdivisionSurfaceMesh.boundaryInterpolation = SubdivisionSurfaceMesh::BoundaryInterpolation::EDGE_ONLY;
        OpenSubdivRefiner openSubdivRefiner(subdivisionSurfaceMesh);

        openSubdivRefiner.refine(1);

        REQUIRE(subdivisionSurfaceMesh.points == std::vector<Vector3f>({{-0.375f, 0, -0.375f},
                                                                        {0.375f, 0, -0.375f},
                                                                        {0.375f, 0, 0.375f},
                                                                        {-0.375f, 0, 0.375f},
                                                                        {0, 0, 0},
                                                                        {0, 0, -0.5},
                                                                        {0.5, 0, 0},
                                                                        {0, 0, 0.5f},
                                                                        {-0.5f, 0, 0}}));
    }

    SECTION("should refine mesh with boundary interpolation edge and corner") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);
        subdivisionSurfaceMesh.boundaryInterpolation = SubdivisionSurfaceMesh::BoundaryInterpolation::EDGE_AND_CORNER;
        OpenSubdivRefiner openSubdivRefiner(subdivisionSurfaceMesh);

        openSubdivRefiner.refine(1);

        REQUIRE(subdivisionSurfaceMesh.points == std::vector<Vector3f>({{-0.5f, 0, -0.5f},
                                                                        {0.5f, 0, -0.5f},
                                                                        {0.5f, 0, 0.5f},
                                                                        {-0.5f, 0, 0.5f},
                                                                        {0, 0, 0},
                                                                        {0, 0, -0.5},
                                                                        {0.5, 0, 0},
                                                                        {0, 0, 0.5f},
                                                                        {-0.5f, 0, 0}}));
    }

    SECTION("should produce limit normals") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);
        OpenSubdivRefiner openSubdivRefiner(subdivisionSurfaceMesh);

        openSubdivRefiner.refine(1);

        REQUIRE(subdivisionSurfaceMesh.normals == std::vector<Vector3f>({
                                                      {0, -0.375, 0},
                                                      {0, -0.375, 0},
                                                      {-0, -0.375, 0},
                                                      {0, -0.375, -0},
                                                      {-0, -30.25, -0},
                                                      {0, -0.171875, 0},
                                                      {0, -0.171875, 0},
                                                      {-0, -0.171875, -0},
                                                      {0, -0.171875, 0},
                                                  }));
    }

    SECTION("should crash when refining mesh with zero ppoints") {
        SubdivisionSurfaceMesh subdivisionSurfaceMesh;
        OpenSubdivRefiner openSubdivRefiner(subdivisionSurfaceMesh);

        openSubdivRefiner.refine(1);

        REQUIRE(subdivisionSurfaceMesh.points.size() == 0);
    }
}

}