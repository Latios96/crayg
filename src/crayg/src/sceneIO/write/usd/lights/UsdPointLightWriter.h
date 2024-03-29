#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDPOINTLIGHTWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDPOINTLIGHTWRITER_H_

#include "scene/lights/Light.h"
#include "sceneIO/write/usd/base/BaseUsdLightWriter.h"
#include <pxr/usd/usdLux/sphereLight.h>

namespace crayg {

class UsdPointLightWriter : public BaseUsdLightWriter<pxr::UsdLuxSphereLight, Light> {
  public:
    UsdPointLightWriter(Light &craygObject);

    pxr::UsdLuxSphereLight write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDPOINTLIGHTWRITER_H_
