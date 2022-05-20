//
// Created by Jan on 19.05.2022.
//

#include "UsdRectLightTranslator.h"
#include "Logger.h"
#include "UsdTranslatorUtils.h"
#include "UsdUtils.h"

namespace crayg {

UsdRectLightTranslator::UsdRectLightTranslator(const pxr::UsdLuxRectLight &rectLight) : rectLight(rectLight) {

}

std::shared_ptr<AreaLight> UsdRectLightTranslator::translate() {
    Logger::debug("Translating rectLight {}", rectLight.GetPath().GetString());
    auto areaLight = std::make_shared<AreaLight>();

    UsdTranslatorUtils::translateTransform(*areaLight, rectLight);

    const auto intensity = UsdUtils::getAttributeValueAs<float>(rectLight.GetIntensityAttr());
    areaLight->setIntensity(intensity);

    const auto width = UsdUtils::getAttributeValueAs<float>(rectLight.GetWidthAttr());
    areaLight->setWidth(width);

    const auto height = UsdUtils::getAttributeValueAs<float>(rectLight.GetHeightAttr());
    areaLight->setHeight(height);

    return areaLight;
}

}