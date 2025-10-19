#include "UsdDiskLightReader.h"
#include "scene/io/usd/UsdUtils.h"

namespace crayg {

std::string UsdDiskLightReader::getTranslatedType() {
    return "diskLight";
}

UsdDiskLightReader::UsdDiskLightReader(const pxr::UsdLuxDiskLight &diskLight) : BaseUsdLightReader(diskLight) {
}

std::shared_ptr<DiskLight> UsdDiskLightReader::read() {
    auto diskLight = BaseUsdLightReader::read();

    const auto radius = UsdUtils::getAttributeValueAs<float>(usdPrim.GetRadiusAttr(), this->timeCodeToRead);
    diskLight->setRadius(radius);

    return diskLight;
}
}