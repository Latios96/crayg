#include "fixtures/SubdivisionSurfaceMeshFixtures.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "sceneIO/usd/UsdReadUtils.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/primitives/UsdSubdivisionSurfaceMeshWriter.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("UsdSubdivisionSurfaceMeshWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory, usdShadingNodeWriteCache);

    SubdivisionSurfaceMesh subdivisionSurfaceMesh;
    subdivisionSurfaceMesh.setTransform(Transform::withPosition(Vector3f(1, 2, 3)));
    SubdivisionSurfaceMeshFixtures::createUnitPlane(subdivisionSurfaceMesh);

    SECTION("should write untesselated subd surface") {
        UsdSubdivisionSurfaceMeshWriter usdSubdivisionSurfaceMeshWriter(subdivisionSurfaceMesh, usdMaterialWriteCache);

        usdSubdivisionSurfaceMeshWriter.write(stage, usdPathFactory);

        auto usdGeomMesh = pxr::UsdGeomMesh(stage->GetPrimAtPath(pxr::SdfPath("/SubdivisionSurfaceMesh0")));
        pxr::GfVec3d translation =
            usdGeomMesh.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default()).ExtractTranslation();
        auto points = UsdUtils::getStaticAttributeValueAs<pxr::VtVec3fArray>(usdGeomMesh.GetPointsAttr());
        auto triangleIndices =
            UsdUtils::getStaticAttributeValueAs<pxr::VtIntArray>(usdGeomMesh.GetFaceVertexIndicesAttr());
        auto faceVertexCounts =
            UsdUtils::getStaticAttributeValueAs<pxr::VtIntArray>(usdGeomMesh.GetFaceVertexCountsAttr());
        auto uvsPrimVar = UsdReadUtils::getAuthoredUvPrimVar(usdGeomMesh);
        pxr::VtVec2fArray uvs;
        pxr::VtIntArray uvIndices;
        uvsPrimVar->Get(&uvs);
        uvsPrimVar->GetIndices(&uvIndices);
        REQUIRE(translation == pxr::GfVec3f(1, 2, -3));
        REQUIRE(points == pxr::VtVec3fArray({{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {0.5, 0, -0.5}, {-0.5, 0, -0.5}}));
        REQUIRE(triangleIndices == pxr::VtIntArray({0, 1, 2, 3}));
        REQUIRE(faceVertexCounts == pxr::VtIntArray({4}));
        REQUIRE(uvs == pxr::VtVec2fArray({{0, 1}, {1, 1}, {0, 0}, {1, 0}}));
        REQUIRE(uvIndices == pxr::VtIntArray({0, 1, 2, 3}));
        REQUIRE_FALSE(usdGeomMesh.GetNormalsAttr().HasAuthoredValue());
    }

    SECTION("should write tesselated subd surface") {
        subdivisionSurfaceMesh.tessellate();
        UsdSubdivisionSurfaceMeshWriter usdSubdivisionSurfaceMeshWriter(subdivisionSurfaceMesh, usdMaterialWriteCache);

        usdSubdivisionSurfaceMeshWriter.write(stage, usdPathFactory);

        auto usdGeomMesh = pxr::UsdGeomMesh(stage->GetPrimAtPath(pxr::SdfPath("/SubdivisionSurfaceMesh0")));
        pxr::GfVec3d translation =
            usdGeomMesh.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default()).ExtractTranslation();
        auto points = UsdUtils::getStaticAttributeValueAs<pxr::VtVec3fArray>(usdGeomMesh.GetPointsAttr());
        auto normals = UsdUtils::getStaticAttributeValueAs<pxr::VtVec3fArray>(usdGeomMesh.GetNormalsAttr());
        auto triangleIndices =
            UsdUtils::getStaticAttributeValueAs<pxr::VtIntArray>(usdGeomMesh.GetFaceVertexIndicesAttr());
        auto faceVertexCounts =
            UsdUtils::getStaticAttributeValueAs<pxr::VtIntArray>(usdGeomMesh.GetFaceVertexCountsAttr());
        auto uvsPrimVar = UsdReadUtils::getAuthoredUvPrimVar(usdGeomMesh);
        pxr::VtVec2fArray uvs;
        pxr::VtIntArray uvIndices;
        uvsPrimVar->Get(&uvs);
        uvsPrimVar->GetIndices(&uvIndices);
        REQUIRE(translation == pxr::GfVec3f(1, 2, -3));
        REQUIRE(points.size() == 81);
        REQUIRE(triangleIndices.size() == 384);
        REQUIRE(faceVertexCounts.size() == 128);
        REQUIRE(uvs.size() == 384);
        REQUIRE(uvIndices.size() == 0);
        REQUIRE_FALSE(normals.empty());
    }
}

}