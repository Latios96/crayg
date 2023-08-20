#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDSPHERELIGHTTRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDSPHERELIGHTTRANSLATOR_H_
#include "scene/lights/Light.h"
#include "sceneIO/read/usd/base/BaseUsdLightReader.h"
#include "sceneIO/usd/CraygUsdBase.h"
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
#endif // CRAYG_SRC_CRAYGUSD_SRC_USDSPHERELIGHTTRANSLATOR_H_
