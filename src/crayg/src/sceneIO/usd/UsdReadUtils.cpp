#include "UsdReadUtils.h"
#include "UsdConversions.h"
#include "Logger.h"
#include "pxr/base/gf/rotation.h"

void crayg::UsdReadUtils::readTransform(crayg::Transformable &transformable,
                                        pxr::UsdGeomXformable &usdGeomXformable) {
    const pxr::GfMatrix4d &d = usdGeomXformable.ComputeLocalToWorldTransform(pxr::UsdTimeCode::Default());
    const Transform &transform = Transform(UsdConversions::convert(d));
    transformable.setTransform(transform);
}
