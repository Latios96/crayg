//
// Created by Jan on 13.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDTRANSLATORUTILS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDTRANSLATORUTILS_H_

#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/usd/usdGeom/xformable.h>
#include "scene/Transformable.h"

namespace crayg {

class UsdReadUtils {
 public:
    static void readTransform(Transformable &transformable, pxr::UsdGeomXformable &usdGeomXformable);
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDTRANSLATORUTILS_H_
