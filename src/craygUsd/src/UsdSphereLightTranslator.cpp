//
// Created by Jan on 13.05.2022.
//

#include "UsdSphereLightTranslator.h"
#include "UsdConversions.h"
#include "UsdTranslatorUtils.h"
#include "UsdUtils.h"

namespace crayg {

UsdSphereLightTranslator::UsdSphereLightTranslator(const pxr::UsdLuxSphereLight &sphereLight)
    : sphereLight(sphereLight) {}

std::shared_ptr<Light> UsdSphereLightTranslator::translate() {
    auto light = std::make_shared<Light>();
    UsdTranslatorUtils::translateTransform(*light, sphereLight);

    const auto intensity = UsdUtils::getAttributeValueAs<float>(sphereLight.GetIntensityAttr());
    light->setIntensity(intensity);

    return light;
}

}

