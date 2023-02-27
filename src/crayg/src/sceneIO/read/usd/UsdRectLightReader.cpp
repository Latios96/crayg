#include "UsdRectLightReader.h"
#include "Logger.h"
#include "sceneIO/usd/UsdReadUtils.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

UsdRectLightReader::UsdRectLightReader(const pxr::UsdLuxRectLight &rectLight) : BaseUsdLightReader(rectLight) {
}

std::shared_ptr<RectLight> UsdRectLightReader::read() {
    auto areaLight = BaseUsdLightReader<pxr::UsdLuxRectLight, RectLight>::read();

    const auto intensity = UsdUtils::getAttributeValueAs<float>(usdPrim.GetIntensityAttr(), this->timeCodeToRead);
    areaLight->setIntensity(intensity);

    const auto width = UsdUtils::getAttributeValueAs<float>(usdPrim.GetWidthAttr(), this->timeCodeToRead);
    areaLight->setWidth(width);

    const auto height = UsdUtils::getAttributeValueAs<float>(usdPrim.GetHeightAttr(), this->timeCodeToRead);
    areaLight->setHeight(height);

    return areaLight;
}

std::string UsdRectLightReader::getTranslatedType() {
    return "rectLight";
}

}