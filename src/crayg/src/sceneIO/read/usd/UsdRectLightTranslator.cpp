//
// Created by Jan on 19.05.2022.
//

#include "UsdRectLightTranslator.h"
#include "Logger.h"
#include "UsdTranslatorUtils.h"
#include "UsdUtils.h"

namespace crayg {

UsdRectLightTranslator::UsdRectLightTranslator(const pxr::UsdLuxRectLight &rectLight) : BaseUsdXformableTranslator(
    rectLight) {
}

std::shared_ptr<RectLight> UsdRectLightTranslator::translate() {
    auto areaLight = BaseUsdXformableTranslator<pxr::UsdLuxRectLight, RectLight>::translate();

    const auto intensity = UsdUtils::getAttributeValueAs<float>(usdPrim.GetIntensityAttr());
    areaLight->setIntensity(intensity);

    const auto width = UsdUtils::getAttributeValueAs<float>(usdPrim.GetWidthAttr());
    areaLight->setWidth(width);

    const auto height = UsdUtils::getAttributeValueAs<float>(usdPrim.GetHeightAttr());
    areaLight->setHeight(height);

    return areaLight;
}
std::string UsdRectLightTranslator::getTranslatedType() {
    return "rectLight";
}

}