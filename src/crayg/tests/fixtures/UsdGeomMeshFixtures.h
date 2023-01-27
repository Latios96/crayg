#ifndef CRAYG_SRC_CRAYG_TESTS_FIXTURES_USDGEOMMESHFIXTURES_H_
#define CRAYG_SRC_CRAYG_TESTS_FIXTURES_USDGEOMMESHFIXTURES_H_

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

class UsdGeomMeshFixtures {
 public:
    static pxr::UsdGeomMesh createQuadPlane(const pxr::UsdStagePtr &stage, const pxr::TfToken &subdivisionScheme=pxr::UsdGeomTokens->none) {
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        usdGeomMesh.GetSubdivisionSchemeAttr().Set(subdivisionScheme);

        pxr::UsdGeomXformCommonAPI(usdGeomMesh).SetTranslate(pxr::GfVec3f(1, 2, 3));
        pxr::VtVec3fArray points {{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points);
        pxr::VtIntArray faceVertexCounts({4});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
        pxr::VtIntArray faceVertexIndices({0, 1, 3, 2});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);

        usdGeomMesh.SetNormalsInterpolation(pxr::UsdGeomTokens->constant);

        return usdGeomMesh;
    }

    static pxr::UsdGeomMesh createTrianglePlane(const pxr::UsdStagePtr &stage) {
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));
        usdGeomMesh.GetSubdivisionSchemeAttr().Set(pxr::UsdGeomTokens->none);

        pxr::UsdGeomXformCommonAPI(usdGeomMesh).SetTranslate(pxr::GfVec3f(1, 2, 3));
        pxr::VtVec3fArray points {{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points);
        pxr::VtIntArray faceVertexCounts({3, 3});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
        pxr::VtIntArray faceVertexIndices({0, 1, 2, 2, 1, 3});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);

        usdGeomMesh.SetNormalsInterpolation(pxr::UsdGeomTokens->constant);

        return usdGeomMesh;
    }
};

} // crayg

#endif //CRAYG_SRC_CRAYG_TESTS_FIXTURES_USDGEOMMESHFIXTURES_H_
