#include <catch2/catch.hpp>
#include "sceneIO/read/usd/UsdMeshReader.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <iostream>
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerVertexPrimVar.h"

namespace crayg {

TEST_CASE("UsdMeshReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdMaterialReadCache usdMaterialTranslationCache;

    SECTION("should read quad plane") {
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        pxr::UsdGeomXformCommonAPI(usdGeomMesh).SetTranslate(pxr::GfVec3f(1, 2, 3));
        pxr::VtVec3fArray points {{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points);
        pxr::VtIntArray faceVertexCounts({4});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
        pxr::VtIntArray faceVertexIndices({0, 1, 3, 2});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(triangleMesh->points
                    == std::vector<Vector3f>({{-0.5, 0, -0.5}, {0.5, 0, -0.5}, {-0.5, 0, 0.5}, {0.5, 0, 0.5}}));
        REQUIRE(
            triangleMesh->faceVertexIndices == std::vector<TriangleMesh::FaceVertexIndices>({{0, 3, 1}, {0, 2, 3}}));
        REQUIRE(triangleMesh->getMaterial()->getName() == "defaultMaterial");
    }

    SECTION("should read triangle plane") {
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        pxr::UsdGeomXformCommonAPI(usdGeomMesh).SetTranslate(pxr::GfVec3f(1, 2, 3));
        pxr::VtVec3fArray points {{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points);
        pxr::VtIntArray faceVertexCounts({3, 3});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
        pxr::VtIntArray faceVertexIndices({0, 1, 2, 2, 1, 3});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(triangleMesh->points
                    == std::vector<Vector3f>({{-0.5, 0, -0.5}, {0.5, 0, -0.5}, {-0.5, 0, 0.5}, {0.5, 0, 0.5}}));
        REQUIRE(
            triangleMesh->faceVertexIndices == std::vector<TriangleMesh::FaceVertexIndices>({{0, 2, 1}, {2, 3, 1}}));
        REQUIRE(triangleMesh->getMaterial()->getName() == "defaultMaterial");
    }

    SECTION("usdGeomMesh with no authored normals should have no normals after translation") {
        // TODO introduce fixtures for meshes
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        pxr::VtVec3fArray points {{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points);
        pxr::VtIntArray faceVertexCounts({3, 3});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
        pxr::VtIntArray faceVertexIndices({0, 1, 2, 2, 1, 3});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->normalsPrimVar == nullptr);
    }

    SECTION("authored faceVarying normals should be translated") {
        // TODO introduce fixtures for meshes
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        pxr::VtVec3fArray points {{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points);
        pxr::VtIntArray faceVertexCounts({3, 3});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
        pxr::VtIntArray faceVertexIndices({0, 1, 2, 2, 1, 3});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);
        usdGeomMesh.SetNormalsInterpolation(pxr::UsdGeomTokens->faceVarying);
        pxr::VtVec3fArray normals({{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}});
        usdGeomMesh.GetNormalsAttr().Set(normals);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->normalsPrimVar != nullptr);
        REQUIRE(*triangleMesh->getNormalsPrimVarAs<TriangleMeshPerVertexPrimVar<Vector3f>>()
                    == std::vector<VertexData<Vector3f>>({
                                                             VertexData(Vector3f {0, 1, 0}),
                                                             VertexData(Vector3f {0, 1, 0}),
                                                         }));
    }

    SECTION("authored normals with normals other than faceVarying should not be translated") {
        // TODO introduce fixtures for meshes
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        pxr::VtVec3fArray points {{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points);
        pxr::VtIntArray faceVertexCounts({3, 3});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
        pxr::VtIntArray faceVertexIndices({0, 1, 2, 2, 1, 3});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);
        usdGeomMesh.SetNormalsInterpolation(pxr::UsdGeomTokens->uniform);
        pxr::VtVec3fArray normals({{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}});
        usdGeomMesh.GetNormalsAttr().Set(normals);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->normalsPrimVar == nullptr);
    }

}

}