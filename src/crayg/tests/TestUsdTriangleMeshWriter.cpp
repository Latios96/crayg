//
// Created by Jan on 28.10.2021.
//


#include <catch2/catch.hpp>
#include "sceneIO/write/usd/UsdTriangleMeshWriter.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>

namespace crayg {

TEST_CASE("UsdTriangleMeshWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory);

    SECTION("should write triangle plane") {
        auto triangleMesh = std::make_shared<TriangleMesh>();
        triangleMesh->setTransform(Transform::withPosition(Vector3f(1, 2, 3)));
        triangleMesh->points = std::vector<Vector3f>({{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}});
        triangleMesh->faceIndices = std::vector<int>({0, 2, 1, 2, 3, 1});
        triangleMesh->init();

        UsdTriangleMeshWriter usdTriangleMeshWriter(triangleMesh, usdMaterialWriteCache);
        usdTriangleMeshWriter.write(stage, usdPathFactory);

        auto usdGeomMesh = pxr::UsdGeomMesh(stage->GetPrimAtPath(pxr::SdfPath("/TriangleMesh0")));
        pxr::GfVec3d
            translation = usdGeomMesh.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default()).ExtractTranslation();
        auto points = UsdUtils::getAttributeValueAs<pxr::VtVec3fArray>(usdGeomMesh.GetPointsAttr());
        auto triangleIndices = UsdUtils::getAttributeValueAs<pxr::VtIntArray>(usdGeomMesh.GetFaceVertexIndicesAttr());
        auto faceVertexCounts = UsdUtils::getAttributeValueAs<pxr::VtIntArray>(usdGeomMesh.GetFaceVertexCountsAttr());
        REQUIRE(translation == pxr::GfVec3f(1, 2, -3));
        REQUIRE(points
                    == pxr::VtVec3fArray({{-0.5, 0, -0.5}, {0.5, 0, -0.5}, {-0.5, 0, 0.5}, {0.5, 0, 0.5}}));
        REQUIRE(triangleIndices == pxr::VtIntArray({0, 1, 2, 2, 1, 3}));
        REQUIRE(faceVertexCounts == pxr::VtIntArray({3, 3}));
    }

}

}