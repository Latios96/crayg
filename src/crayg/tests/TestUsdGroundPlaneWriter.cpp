#include <catch2/catch.hpp>
#include "sceneIO/write/usd/UsdGroundPlaneWriter.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>

namespace crayg {

TEST_CASE("UsdGroundPlaneMeshWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory);

    SECTION("should write groundPlane") {
        auto groundPlane = std::make_shared<GroundPlane>();

        UsdGroundPlaneWriter usdGroundPlaneWriter(groundPlane, usdMaterialWriteCache);
        usdGroundPlaneWriter.write(stage, usdPathFactory);

        auto usdGeomMesh = pxr::UsdGeomMesh(stage->GetPrimAtPath(pxr::SdfPath("/GroundPlane0")));
        pxr::GfVec3d
            translation = usdGeomMesh.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default()).ExtractTranslation();
        auto points = UsdUtils::getAttributeValueAs<pxr::VtVec3fArray>(usdGeomMesh.GetPointsAttr());
        auto triangleIndices = UsdUtils::getAttributeValueAs<pxr::VtIntArray>(usdGeomMesh.GetFaceVertexIndicesAttr());
        auto faceVertexCounts = UsdUtils::getAttributeValueAs<pxr::VtIntArray>(usdGeomMesh.GetFaceVertexCountsAttr());
        REQUIRE(translation == pxr::GfVec3f(0, 0, 0));
        REQUIRE(points
                    == pxr::VtVec3fArray({{-1000, 0, 1000}, {-1000, 0, -1000}, {1000, 0, -1000}, {1000, 0, 1000}}));
        REQUIRE(triangleIndices == pxr::VtIntArray({0, 2, 1, 2, 0, 3}));
        REQUIRE(faceVertexCounts == pxr::VtIntArray({3, 3}));
    }

}

}