//
// Created by Jan on 28.10.2021.
//


#include <catch2/catch.hpp>
#include <UsdMeshTranslator.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <iostream>

namespace crayg {

TEST_CASE("MeshTranslatorTranslate") {

    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should translate quad plane") {
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        pxr::UsdGeomXformCommonAPI(usdGeomMesh).SetTranslate(pxr::GfVec3f(1, 2, 3));
        pxr::VtVec3fArray points {{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points);
        pxr::VtIntArray faceVertexCounts({4});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
        pxr::VtIntArray faceVertexIndices({0, 1, 3, 2});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);

        UsdMeshTranslator meshTranslator(usdGeomMesh);
        auto triangleMesh = meshTranslator.translate();

        REQUIRE(triangleMesh->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(triangleMesh->points
                    == std::vector<Vector3f>({{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}}));
        REQUIRE(triangleMesh->faceIndexes == std::vector<int>({0, 1, 3, 0, 3, 2}));
    }

    SECTION("should translate triangle plane") {
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        pxr::UsdGeomXformCommonAPI(usdGeomMesh).SetTranslate(pxr::GfVec3f(1, 2, 3));
        pxr::VtVec3fArray points {{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points);
        pxr::VtIntArray faceVertexCounts({3, 3});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
        pxr::VtIntArray faceVertexIndices({0, 1, 2, 2, 1, 3});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);

        UsdMeshTranslator meshTranslator(usdGeomMesh);
        auto triangleMesh = meshTranslator.translate();

        REQUIRE(triangleMesh->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(triangleMesh->points
                    == std::vector<Vector3f>({{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}}));
        REQUIRE(triangleMesh->faceIndexes == std::vector<int>({0, 1, 2, 2, 1, 3}));
    }

}

}