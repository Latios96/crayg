#pragma once

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
