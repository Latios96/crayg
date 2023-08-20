#include "fixtures/UsdGeomMeshFixtures.h"
#include "sceneIO/read/usd/primitives/UsdSubdivisionSurfaceMeshReader.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("UsdSubdivisionSurfaceMeshReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdMaterialReadCache usdMaterialTranslationCache;

    SECTION("should not read non-catmull clark mesh") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createQuadPlane(stage);

        UsdSubdivisionSurfaceMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        REQUIRE_THROWS_AS(usdMeshReader.read(), std::runtime_error);
    }

    SECTION("should read catmull clark plane") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createQuadPlane(stage, pxr::UsdGeomTokens->catmullClark);

        UsdSubdivisionSurfaceMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto subdivisionSurfaceMesh = usdMeshReader.read();

        REQUIRE(subdivisionSurfaceMesh->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(subdivisionSurfaceMesh->points ==
                std::vector<Vector3f>({{-0.5, 0, -0.5}, {0.5, 0, -0.5}, {-0.5, 0, 0.5}, {0.5, 0, 0.5}}));
        REQUIRE(subdivisionSurfaceMesh->faceVertexIndices == std::vector<int>({2, 3, 1, 0}));
        REQUIRE(subdivisionSurfaceMesh->faceVertexCounts == std::vector<int>({4}));
        REQUIRE(subdivisionSurfaceMesh->getMaterial()->getName() == "defaultMaterial");
    }

    SECTION("should not read unsupported normals interpolation") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createQuadPlane(stage, pxr::UsdGeomTokens->catmullClark);
        usdGeomMesh.SetNormalsInterpolation(pxr::UsdGeomTokens->vertex);
        pxr::VtVec3fArray normals({{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}});

        UsdSubdivisionSurfaceMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto subdivisionSurfaceMesh = usdMeshReader.read();

        REQUIRE(subdivisionSurfaceMesh->normals.empty());
    }

    SECTION("should read boundary interpolation attr") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createQuadPlane(stage, pxr::UsdGeomTokens->catmullClark);
        usdGeomMesh.GetInterpolateBoundaryAttr().Set(pxr::UsdGeomTokens->edgeAndCorner);

        UsdSubdivisionSurfaceMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto subdivisionSurfaceMesh = usdMeshReader.read();

        REQUIRE(subdivisionSurfaceMesh->boundaryInterpolation ==
                SubdivisionSurfaceMesh::BoundaryInterpolation::EDGE_AND_CORNER);
    }

    SECTION("should read boundary interpolation attr none as edge only") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createQuadPlane(stage, pxr::UsdGeomTokens->catmullClark);
        usdGeomMesh.GetInterpolateBoundaryAttr().Set(pxr::UsdGeomTokens->none);

        UsdSubdivisionSurfaceMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto subdivisionSurfaceMesh = usdMeshReader.read();

        REQUIRE(subdivisionSurfaceMesh->boundaryInterpolation ==
                SubdivisionSurfaceMesh::BoundaryInterpolation::EDGE_ONLY);
    }
}

}