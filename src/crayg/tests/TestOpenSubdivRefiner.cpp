#include <catch2/catch.hpp>
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "fixtures/SubdivisionSurfaceMeshFixtures.h"
#include "scene/primitives/subdivisionsurfacemesh/OpenSubdivRefiner.h"

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
        REQUIRE(subdivisionSurfaceMesh.faceVertexIndices
                    == std::vector<int>({0, 5, 4, 8, 5, 1, 6, 4, 4, 6, 2, 7, 8, 4, 7, 3}));
        REQUIRE(subdivisionSurfaceMesh.faceVertexCounts == std::vector<int>({4, 4, 4, 4}));
    }
}

}