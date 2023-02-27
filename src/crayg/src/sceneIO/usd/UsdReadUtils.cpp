#include "UsdReadUtils.h"
#include "Logger.h"
#include "UsdConversions.h"
#include "pxr/base/gf/rotation.h"

void crayg::UsdReadUtils::readTransform(crayg::Transformable &transformable, pxr::UsdGeomXformable &usdGeomXformable,
                                        const pxr::UsdTimeCode &timeToRead) {
    const pxr::GfMatrix4d &d = usdGeomXformable.ComputeLocalToWorldTransform(timeToRead);
    const Transform &transform = Transform(UsdConversions::convert(d));
    transformable.setTransform(transform);
}
