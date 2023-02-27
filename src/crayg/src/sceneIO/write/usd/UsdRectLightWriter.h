#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRECTLIGHTWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRECTLIGHTWRITER_H_

#include "scene/lights/RectLight.h"
#include "sceneIO/write/usd/BaseUsdLightWriter.h"
#include <pxr/usd/usdLux/rectLight.h>

namespace crayg {

class UsdRectLightWriter : public BaseUsdLightWriter<pxr::UsdLuxRectLight, RectLight> {
  public:
    UsdRectLightWriter(RectLight &craygObject);

    pxr::UsdLuxRectLight write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRECTLIGHTWRITER_H_
