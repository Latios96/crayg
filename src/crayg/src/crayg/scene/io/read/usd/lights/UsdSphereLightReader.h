#pragma once
#include "crayg/scene/io/read/usd/base/BaseUsdLightReader.h"
#include "crayg/scene/lights/Light.h"
#include <pxr/usd/usdLux/sphereLight.h>

namespace crayg {

class UsdSphereLightReader : public BaseUsdLightReader<pxr::UsdLuxSphereLight, Light> {
  public:
    UsdSphereLightReader(const pxr::UsdLuxSphereLight &sphereLight);
    std::shared_ptr<Light> read() override;

  protected:
    std::string getTranslatedType() override;
};

}
