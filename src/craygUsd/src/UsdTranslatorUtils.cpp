//
// Created by Jan on 13.05.2022.
//

#include "UsdTranslatorUtils.h"
#include "UsdConversions.h"

void crayg::UsdTranslatorUtils::translateTransform(crayg::Transformable &transformable,
                                                   pxr::UsdGeomXformable &usdGeomXformable) {
    pxr::GfMatrix4d matrix;
    bool resetsXformStack = false;
    usdGeomXformable.GetLocalTransformation(&matrix, &resetsXformStack);
    transformable.setTransform(Transform(UsdConversions::convert(matrix)));
}
