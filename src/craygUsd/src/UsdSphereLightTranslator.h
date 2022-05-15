//
// Created by Jan on 13.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDSPHERELIGHTTRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDSPHERELIGHTTRANSLATOR_H_
#include "CraygUsdBase.h"
#include "scene/Light.h"
#include <pxr/usd/usdLux/sphereLight.h>

namespace crayg {

class UsdSphereLightTranslator {
 public:
    UsdSphereLightTranslator(const pxr::UsdLuxSphereLight &sphereLight);
    std::shared_ptr<Light> translate();
 private:
    pxr::UsdLuxSphereLight sphereLight;
};

}
#endif //CRAYG_SRC_CRAYGUSD_SRC_USDSPHERELIGHTTRANSLATOR_H_
