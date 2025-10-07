#include "basics/Vector2_formatter.h"
#include "fixtures/UsdGeomMeshFixtures.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerPointPrimVar.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerVertexPrimVar.h"
#include "sceneIO/read/usd/primitives/UsdMeshReader.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/primvarsAPI.h>

namespace crayg {

TEST_CASE("UsdMeshReader::read") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdMaterialReadCache usdMaterialTranslationCache;

    SECTION("should read quad plane") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createQuadPlane(stage);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(triangleMesh->points ==
                std::vector<Vector3f>({{-0.5, 0, -0.5}, {0.5, 0, -0.5}, {-0.5, 0, 0.5}, {0.5, 0, 0.5}}));
        REQUIRE(triangleMesh->faceVertexIndices ==
                std::vector<TriangleMesh::FaceVertexIndices>({{0, 3, 1}, {0, 2, 3}}));
        REQUIRE(triangleMesh->getMaterial()->getName() == "defaultMaterial");
    }

    SECTION("should read triangle plane") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createTrianglePlane(stage);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(triangleMesh->points ==
                std::vector<Vector3f>({{-0.5, 0, -0.5}, {0.5, 0, -0.5}, {-0.5, 0, 0.5}, {0.5, 0, 0.5}}));
        REQUIRE(triangleMesh->faceVertexIndices ==
                std::vector<TriangleMesh::FaceVertexIndices>({{0, 2, 1}, {2, 3, 1}}));
        REQUIRE(triangleMesh->getMaterial()->getName() == "defaultMaterial");
    }

    SECTION("usdGeomMesh with no authored normals should have no normals after translation") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createTrianglePlane(stage);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->normalsPrimVar == nullptr);
    }

    SECTION("authored faceVarying normals should be translated") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createTrianglePlane(stage);

        usdGeomMesh.SetNormalsInterpolation(pxr::UsdGeomTokens->faceVarying);
        pxr::VtVec3fArray normals({{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}});
        usdGeomMesh.GetNormalsAttr().Set(normals);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->normalsPrimVar != nullptr);
        REQUIRE(*triangleMesh->getNormalsPrimVarAs<TriangleMeshPerVertexPrimVar<Vector3f>>() ==
                std::vector<VertexData<Vector3f>>({
                    VertexData(Vector3f{0, 1, 0}),
                    VertexData(Vector3f{0, 1, 0}),
                }));
    }

    SECTION("authored vertex normals should be translated") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createTrianglePlane(stage);

        usdGeomMesh.SetNormalsInterpolation(pxr::UsdGeomTokens->vertex);
        pxr::VtVec3fArray normals({{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}});
        usdGeomMesh.GetNormalsAttr().Set(normals);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->normalsPrimVar != nullptr);
        REQUIRE(*triangleMesh->getNormalsPrimVarAs<TriangleMeshPerPointPrimVar<Vector3f>>() ==
                std::vector<Vector3f>({{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}}));
    }

    SECTION("authored normals with unsupported interpolation should not be translated") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createTrianglePlane(stage);

        usdGeomMesh.SetNormalsInterpolation(pxr::UsdGeomTokens->uniform);
        pxr::VtVec3fArray normals({{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}});
        usdGeomMesh.GetNormalsAttr().Set(normals);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->normalsPrimVar == nullptr);
    }

    SECTION("should read mesh with animated geometry definitions correctly") {
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        pxr::UsdGeomXformCommonAPI(usdGeomMesh).SetTranslate(pxr::GfVec3f(1, 2, 3));
        pxr::VtVec3fArray points{{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points, pxr::UsdTimeCode());
        pxr::VtIntArray faceVertexCounts({4});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts, pxr::UsdTimeCode());
        pxr::VtIntArray faceVertexIndices({0, 1, 3, 2});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices, pxr::UsdTimeCode());
        usdGeomMesh.SetNormalsInterpolation(pxr::UsdGeomTokens->constant);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->getTransform().toPosition() == Vector3f(1, 2, -3));
        REQUIRE(triangleMesh->points ==
                std::vector<Vector3f>({{-0.5, 0, -0.5}, {0.5, 0, -0.5}, {-0.5, 0, 0.5}, {0.5, 0, 0.5}}));
        REQUIRE(triangleMesh->faceVertexIndices ==
                std::vector<TriangleMesh::FaceVertexIndices>({{0, 3, 1}, {0, 2, 3}}));
    }

    SECTION("usdGeomMesh with no authored uvs should have no uvs after translation") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createTrianglePlane(stage);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->uvsPrimVar == nullptr);
    }

    SECTION("authored faceVarying uvs should be translated for triangle mesh") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createTrianglePlane(stage);
        pxr::UsdGeomPrimvarsAPI primvarsApi(usdGeomMesh);

        auto uvsPrimvar = primvarsApi.CreatePrimvar(pxr::TfToken("st"), pxr::SdfValueTypeNames->TexCoord2fArray,
                                                    pxr::UsdGeomTokens->faceVarying);
        pxr::VtVec2fArray uvs({{1, 0}, {1, 1}, {0, 0}, {1, 0}});
        pxr::VtIntArray uvIndices({0, 1, 2, 2, 1, 3});
        uvsPrimvar.Set(uvs);
        uvsPrimvar.SetIndices(uvIndices);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->uvsPrimVar != nullptr);
        REQUIRE(*triangleMesh->getUvsPrimVarAs<TriangleMeshPerVertexPrimVar<Vector2f>>() ==
                std::vector<VertexData<Vector2f>>({
                    VertexData(Vector2f{1, 0}, Vector2f{0, 0}, Vector2f{1, 1}),
                    VertexData(Vector2f{0, 0}, Vector2f{1, 0}, Vector2f{1, 1}),

                }));
    }

    SECTION("authored faceVarying uvs should be translated for quad mesh") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createQuadPlane(stage);
        pxr::UsdGeomPrimvarsAPI primvarsApi(usdGeomMesh);

        auto uvsPrimvar = primvarsApi.CreatePrimvar(pxr::TfToken("st"), pxr::SdfValueTypeNames->TexCoord2fArray,
                                                    pxr::UsdGeomTokens->faceVarying);
        pxr::VtVec2fArray uvs({{0, 0}, {1, 0}, {0, 1}, {1, 1}});
        pxr::VtIntArray uvIndices({0, 1, 3, 2});
        uvsPrimvar.Set(uvs);
        uvsPrimvar.SetIndices(uvIndices);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->uvsPrimVar != nullptr);
        REQUIRE(*triangleMesh->getUvsPrimVarAs<TriangleMeshPerVertexPrimVar<Vector2f>>() ==
                std::vector<VertexData<Vector2f>>({
                    VertexData(Vector2f{0, 0}, Vector2f{1, 1}, Vector2f{1, 0}),
                    VertexData(Vector2f{0, 0}, Vector2f{0, 1}, Vector2f{1, 1}),
                }));
    }

    SECTION("authored vertex uvs should be translated for triangle mesh") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createTrianglePlane(stage);
        pxr::UsdGeomPrimvarsAPI primvarsApi(usdGeomMesh);

        auto uvsPrimvar = primvarsApi.CreatePrimvar(pxr::TfToken("st"), pxr::SdfValueTypeNames->TexCoord2fArray,
                                                    pxr::UsdGeomTokens->vertex);
        pxr::VtVec2fArray uvs({{1, 0}, {1, 1}, {0, 0}, {1, 0}});
        uvsPrimvar.Set(uvs);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->uvsPrimVar != nullptr);
        REQUIRE(*triangleMesh->getUvsPrimVarAs<TriangleMeshPerPointPrimVar<Vector2f>>() ==
                std::vector<Vector2f>({{1, 0}, {1, 1}, {0, 0}, {1, 0}}));
    }

    SECTION("authored uvs with unsupported interpolation should not be translated") {
        auto usdGeomMesh = UsdGeomMeshFixtures::createQuadPlane(stage);
        pxr::UsdGeomPrimvarsAPI primvarsApi(usdGeomMesh);

        auto uvsPrimvar = primvarsApi.CreatePrimvar(pxr::TfToken("st"), pxr::SdfValueTypeNames->TexCoord2fArray,
                                                    pxr::UsdGeomTokens->uniform);
        pxr::VtVec2fArray uvs({{0, 0}, {1, 0}, {0, 1}, {1, 1}});
        pxr::VtIntArray uvIndices({0, 1, 3, 2});
        uvsPrimvar.Set(uvs);
        uvsPrimvar.SetIndices(uvIndices);

        UsdMeshReader usdMeshReader(usdGeomMesh, usdMaterialTranslationCache);
        auto triangleMesh = usdMeshReader.read();

        REQUIRE(triangleMesh->uvsPrimVar == nullptr);
    }
}

}