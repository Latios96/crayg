//
// Created by Jan on 13.05.2022.
//

#include "UsdSphereLightTranslator.h"
#include "UsdConversions.h"
#include "UsdTranslatorUtils.h"
#include "UsdUtils.h"
#include "Logger.h"

namespace crayg {

UsdSphereLightTranslator::UsdSphereLightTranslator(const pxr::UsdLuxSphereLight &sphereLight)
    : BaseUsdXformableTranslator(sphereLight) {}

std::shared_ptr<Light> UsdSphereLightTranslator::translate() {
    auto light = BaseUsdXformableTranslator<pxr::UsdLuxSphereLight, Light>::translate();

    const auto intensity = UsdUtils::getAttributeValueAs<float>(usdPrim.GetIntensityAttr());
    light->setIntensity(intensity);

    return light;
}
std::string UsdSphereLightTranslator::getTranslatedType() {
    return "sphereLight";
}

}

