//
// Created by Jan on 19.05.2022.
//

#include "UsdRectLightReader.h"
#include "Logger.h"
#include "sceneIO/usd/UsdReadUtils.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

UsdRectLightReader::UsdRectLightReader(const pxr::UsdLuxRectLight &rectLight) : BaseUsdLightReader(
    rectLight) {
}

std::shared_ptr<RectLight> UsdRectLightReader::read() {
    auto areaLight = BaseUsdLightReader<pxr::UsdLuxRectLight, RectLight>::read();

    const auto intensity = UsdUtils::getAttributeValueAs<float>(usdPrim.GetIntensityAttr());
    areaLight->setIntensity(intensity);

    const auto width = UsdUtils::getAttributeValueAs<float>(usdPrim.GetWidthAttr());
    areaLight->setWidth(width);

    const auto height = UsdUtils::getAttributeValueAs<float>(usdPrim.GetHeightAttr());
    areaLight->setHeight(height);

    return areaLight;
}
std::string UsdRectLightReader::getTranslatedType() {
    return "rectLight";
}

}