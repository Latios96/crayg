#include "UsdReadUtils.h"
#include "Logger.h"
#include "UsdConversions.h"
#include "UsdUtils.h"
#include "pxr/base/gf/rotation.h"
#include "pxr/usd/usdGeom/mesh.h"

void crayg::UsdReadUtils::readTransform(crayg::Transformable &transformable, pxr::UsdGeomXformable &usdGeomXformable,
                                        const pxr::UsdTimeCode &timeToRead) {
    const pxr::GfMatrix4d &d = usdGeomXformable.ComputeLocalToWorldTransform(timeToRead);
    const Transform &transform = Transform(UsdConversions::convert(d));
    transformable.setTransform(transform);
}

bool crayg::UsdReadUtils::isSubdivisionSurfaceMesh(pxr::UsdPrim &prim) {
    if (!prim.IsA<pxr::UsdGeomMesh>()) {
        return false;
    }
    pxr::UsdGeomMesh usdGeomMesh(prim);
    auto subdivisionScheme = UsdUtils::getAttributeValueAs<pxr::TfToken>(usdGeomMesh.GetSubdivisionSchemeAttr(),
                                                                         pxr::UsdTimeCode::EarliestTime());
    return subdivisionScheme == pxr::UsdGeomTokens->catmullClark;
}

bool crayg::UsdReadUtils::primIsVisible(pxr::UsdPrim &prim) {
    return pxr::UsdGeomImageable(prim).ComputeVisibility() != pxr::TfToken("invisible");
}
