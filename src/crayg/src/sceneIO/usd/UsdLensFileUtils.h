#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_USD_USDLENSFILEUTILS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_USD_USDLENSFILEUTILS_H_

#include "scene/camera/realistic/CameraLens.h"
#include <pxr/usd/usd/prim.h>

namespace crayg {

class UsdLensFileUtils {
  public:
    static void writeEmbeddedLensFile(const CameraLens &cameraLens, pxr::UsdPrim prim);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_USD_USDLENSFILEUTILS_H_
