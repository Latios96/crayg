//
// Created by Jan on 13.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDSPHERELIGHTTRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDSPHERELIGHTTRANSLATOR_H_
#include "CraygUsdBase.h"
#include "BaseUsdXformableTranslator.h"
#include "scene/Light.h"
#include <pxr/usd/usdLux/sphereLight.h>

namespace crayg {

class UsdSphereLightTranslator : public BaseUsdXformableTranslator<pxr::UsdLuxSphereLight, Light> {
 public:
    UsdSphereLightTranslator(const pxr::UsdLuxSphereLight &sphereLight);
    std::shared_ptr<Light> translate() override;
 protected:
    std::string getTranslatedType() override;
};

}
#endif //CRAYG_SRC_CRAYGUSD_SRC_USDSPHERELIGHTTRANSLATOR_H_
