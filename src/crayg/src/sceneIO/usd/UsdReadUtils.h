#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDTRANSLATORUTILS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDTRANSLATORUTILS_H_

#include "scene/Transformable.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/primvarsAPI.h>
#include <pxr/usd/usdGeom/xformable.h>

namespace crayg {

class UsdReadUtils {
  public:
    static void readTransform(Transformable &transformable, pxr::UsdGeomXformable &usdGeomXformable,
                              const pxr::UsdTimeCode &timeToRead);
    static bool isSubdivisionSurfaceMesh(pxr::UsdPrim &prim);
    static bool primIsVisible(pxr::UsdPrim &prim);
    static std::optional<pxr::UsdGeomPrimvar> getAuthoredUvPrimVar(const pxr::UsdGeomMesh &mesh);
};

}

#endif // CRAYG_SRC_CRAYGUSD_SRC_USDTRANSLATORUTILS_H_
