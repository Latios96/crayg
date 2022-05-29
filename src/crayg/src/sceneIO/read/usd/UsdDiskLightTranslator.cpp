//
// Created by Jan on 21.05.2022.
//

#include "UsdDiskLightTranslator.h"
#include "UsdUtils.h"

namespace crayg {

std::string UsdDiskLightTranslator::getTranslatedType() {
    return "diskLight";
}
UsdDiskLightTranslator::UsdDiskLightTranslator(const pxr::UsdLuxDiskLight &diskLight) : BaseUsdLightTranslator(
    diskLight) {

}
std::shared_ptr<DiskLight> UsdDiskLightTranslator::translate() {
    auto diskLight = BaseUsdLightTranslator::translate();

    const auto intensity = UsdUtils::getAttributeValueAs<float>(usdPrim.GetIntensityAttr());
    diskLight->setIntensity(intensity);

    const auto radius = UsdUtils::getAttributeValueAs<float>(usdPrim.GetRadiusAttr());
    diskLight->setRadius(radius);

    return diskLight;
}
} // crayg