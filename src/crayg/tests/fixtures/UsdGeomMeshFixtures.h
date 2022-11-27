#ifndef CRAYG_SRC_CRAYG_TESTS_FIXTURES_USDGEOMMESHFIXTURES_H_
#define CRAYG_SRC_CRAYG_TESTS_FIXTURES_USDGEOMMESHFIXTURES_H_

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

namespace crayg {

class UsdGeomMeshFixtures {
 public:
    static pxr::UsdGeomMesh createQuadPlane(const pxr::UsdStagePtr &stage) {
        auto usdGeomMesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/usdMesh"));

        pxr::UsdGeomXformCommonAPI(usdGeomMesh).SetTranslate(pxr::GfVec3f(1, 2, 3));
        pxr::VtVec3fArray points {{-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5}};
        usdGeomMesh.GetPointsAttr().Set(points);
        pxr::VtIntArray faceVertexCounts({4});
        usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
        pxr::VtIntArray faceVertexIndices({0, 1, 3, 2});
        usdGeomMesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);

        return usdGeomMesh;
    }
};

} // crayg

#endif //CRAYG_SRC_CRAYG_TESTS_FIXTURES_USDGEOMMESHFIXTURES_H_
