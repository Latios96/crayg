//
// Created by Jan on 21.05.2022.
//

#include "UsdDiskLightReader.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

std::string UsdDiskLightReader::getTranslatedType() {
    return "diskLight";
}
UsdDiskLightReader::UsdDiskLightReader(const pxr::UsdLuxDiskLight &diskLight) : BaseUsdLightReader(
    diskLight) {

}
std::shared_ptr<DiskLight> UsdDiskLightReader::read() {
    auto diskLight = BaseUsdLightReader::read();

    const auto intensity = UsdUtils::getAttributeValueAs<float>(usdPrim.GetIntensityAttr());
    diskLight->setIntensity(intensity);

    const auto radius = UsdUtils::getAttributeValueAs<float>(usdPrim.GetRadiusAttr());
    diskLight->setRadius(radius);

    return diskLight;
}
} // crayg