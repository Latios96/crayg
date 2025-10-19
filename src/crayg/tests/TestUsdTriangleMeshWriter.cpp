#include "fixtures/TriangleMeshFixtures.h"
#include "scene/io/usd/UsdUtils.h"
#include "scene/io/write/usd/primitives/UsdTriangleMeshWriter.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerPointPrimVar.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerVertexPrimVar.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/primvarsAPI.h>

namespace crayg {

TEST_CASE("UsdTriangleMeshWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory, usdShadingNodeWriteCache);

    SECTION("should write triangle plane") {
        TriangleMesh triangleMesh;
        triangleMesh.setTransform(Transform::withPosition(Vector3f(1, 2, 3)));
        triangleMesh.points = std::vector<Vector3f>({{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}});
        triangleMesh.faceVertexIndices = std::vector<TriangleMesh::FaceVertexIndices>({{0, 2, 1}, {2, 3, 1}});
        triangleMesh.init();

        UsdTriangleMeshWriter usdTriangleMeshWriter(triangleMesh, usdMaterialWriteCache);
        usdTriangleMeshWriter.write(stage, usdPathFactory);

        auto usdGeomMesh = pxr::UsdGeomMesh(stage->GetPrimAtPath(pxr::SdfPath("/TriangleMesh0")));
        pxr::GfVec3d translation =
            usdGeomMesh.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default()).ExtractTranslation();
        auto points = UsdUtils::getStaticAttributeValueAs<pxr::VtVec3fArray>(usdGeomMesh.GetPointsAttr());
        auto triangleIndices =
            UsdUtils::getStaticAttributeValueAs<pxr::VtIntArray>(usdGeomMesh.GetFaceVertexIndicesAttr());
        auto faceVertexCounts =
            UsdUtils::getStaticAttributeValueAs<pxr::VtIntArray>(usdGeomMesh.GetFaceVertexCountsAttr());
        REQUIRE(translation == pxr::GfVec3f(1, 2, -3));
        REQUIRE(points == pxr::VtVec3fArray({{-0.5, 0, -0.5}, {0.5, 0, -0.5}, {-0.5, 0, 0.5}, {0.5, 0, 0.5}}));
        REQUIRE(triangleIndices == pxr::VtIntArray({0, 1, 2, 2, 1, 3}));
        REQUIRE(faceVertexCounts == pxr::VtIntArray({3, 3}));
    }

    SECTION("should write per point normals") {
        auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();
        auto primVar = triangleMesh->addNormalsPrimVar<TriangleMeshPerPointPrimVar<Vector3f>>();
        primVar->write(0, Vector3f(1, 0, 0));
        primVar->write(1, Vector3f(0, 1, 0));
        primVar->write(2, Vector3f(0, 0, 1));
        primVar->write(3, Vector3f(1, 0, 0));
        primVar->write(4, Vector3f(0, 1, 0));
        primVar->write(5, Vector3f(0, 0, 1));

        UsdTriangleMeshWriter usdTriangleMeshWriter(*triangleMesh, usdMaterialWriteCache);
        usdTriangleMeshWriter.write(stage, usdPathFactory);

        auto usdGeomMesh = pxr::UsdGeomMesh(stage->GetPrimAtPath(pxr::SdfPath("/TriangleMesh0")));
        REQUIRE(usdGeomMesh.GetNormalsInterpolation() == pxr::UsdGeomTokens->vertex);
        auto normals = UsdUtils::getStaticAttributeValueAs<pxr::VtVec3fArray>(usdGeomMesh.GetNormalsAttr());
        REQUIRE(normals == pxr::VtVec3fArray({{1, 0, -0}, {0, 1, -0}, {0, 0, -1}, {1, 0, -0}, {0, 1, -0}, {0, 0, -1}}));
    }

    SECTION("should write per vertex normals") {
        auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();
        auto primVar = triangleMesh->addNormalsPrimVar<TriangleMeshPerVertexPrimVar<Vector3f>>();
        primVar->write(0, VertexData(Vector3f(1, 0, 0)));
        primVar->write(1, VertexData(Vector3f(0, 1, 0)));
        primVar->write(2, VertexData(Vector3f(0, 0, 1)));
        primVar->write(3, VertexData(Vector3f(1, 0, 0)));

        UsdTriangleMeshWriter usdTriangleMeshWriter(*triangleMesh, usdMaterialWriteCache);
        usdTriangleMeshWriter.write(stage, usdPathFactory);

        auto usdGeomMesh = pxr::UsdGeomMesh(stage->GetPrimAtPath(pxr::SdfPath("/TriangleMesh0")));
        REQUIRE(usdGeomMesh.GetNormalsInterpolation() == pxr::UsdGeomTokens->faceVarying);
        auto normals = UsdUtils::getStaticAttributeValueAs<pxr::VtVec3fArray>(usdGeomMesh.GetNormalsAttr());
        REQUIRE(normals == pxr::VtVec3fArray({{1, 0, -0},
                                              {1, 0, -0},
                                              {1, 0, -0},
                                              {0, 1, -0},
                                              {0, 1, -0},
                                              {0, 1, -0},
                                              {0, 0, -1},
                                              {0, 0, -1},
                                              {0, 0, -1},
                                              {1, 0, -0},
                                              {1, 0, -0},
                                              {1, 0, -0}}));
    }

    SECTION("should write per vertex uvs") {
        auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();
        auto primVar = triangleMesh->addUvsPrimVar<TriangleMeshPerVertexPrimVar<Vector2f>>();
        primVar->write(0, VertexData(Vector2f(0, 1), Vector2f(0, 0), Vector2f(1, 1)));
        primVar->write(1, VertexData(Vector2f(1, 1), Vector2f(0, 0), Vector2f(1, 0)));
        primVar->write(2, VertexData(Vector2f(1, 1), Vector2f(1, 0), Vector2f(2, 1)));
        primVar->write(3, VertexData(Vector2f(2, 1), Vector2f(1, 0), Vector2f(2, 0)));

        UsdTriangleMeshWriter usdTriangleMeshWriter(*triangleMesh, usdMaterialWriteCache);
        usdTriangleMeshWriter.write(stage, usdPathFactory);

        auto usdGeomMesh = pxr::UsdGeomMesh(stage->GetPrimAtPath(pxr::SdfPath("/TriangleMesh0")));
        pxr::UsdGeomPrimvarsAPI primvarsApi(usdGeomMesh);

        auto uvsPrimvar = primvarsApi.GetPrimvar(pxr::TfToken("st"));
        REQUIRE(uvsPrimvar.GetInterpolation() == pxr::UsdGeomTokens->faceVarying);
        auto uvs = UsdUtils::getStaticAttributeValueAs<pxr::VtVec2fArray>(uvsPrimvar);
        REQUIRE(uvs ==
                pxr::VtVec2fArray(
                    {{0, 1}, {1, 1}, {0, 0}, {1, 1}, {1, 0}, {0, 0}, {1, 1}, {2, 1}, {1, 0}, {2, 1}, {2, 0}, {1, 0}}));
    }

    SECTION("should write per point uvs") {
        auto triangleMesh = TriangleMeshFixtures::createPrimVarFixtureMesh();
        auto primVar = triangleMesh->addUvsPrimVar<TriangleMeshPerPointPrimVar<Vector2f>>();
        primVar->write(0, Vector2f(1, 0));
        primVar->write(1, Vector2f(0, 1));
        primVar->write(2, Vector2f(1, 1));
        primVar->write(3, Vector2f(0, 0));
        primVar->write(4, Vector2f(1, 0));
        primVar->write(5, Vector2f(0, 1));

        UsdTriangleMeshWriter usdTriangleMeshWriter(*triangleMesh, usdMaterialWriteCache);
        usdTriangleMeshWriter.write(stage, usdPathFactory);

        auto usdGeomMesh = pxr::UsdGeomMesh(stage->GetPrimAtPath(pxr::SdfPath("/TriangleMesh0")));
        pxr::UsdGeomPrimvarsAPI primvarsApi(usdGeomMesh);

        auto uvsPrimvar = primvarsApi.GetPrimvar(pxr::TfToken("st"));
        REQUIRE(uvsPrimvar.GetInterpolation() == pxr::UsdGeomTokens->vertex);
        auto uvs = UsdUtils::getStaticAttributeValueAs<pxr::VtVec2fArray>(uvsPrimvar);
        REQUIRE(uvs == pxr::VtVec2fArray({{1, 0}, {0, 1}, {1, 1}, {0, 0}, {1, 0}, {0, 1}}));
    }
}

}