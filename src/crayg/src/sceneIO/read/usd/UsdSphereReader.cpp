#include "UsdSphereReader.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

UsdSphereReader::UsdSphereReader(const pxr::UsdGeomSphere &usdPrim, UsdMaterialReadCache &usdMaterialTranslationCache)
    : BaseUsdImageableReader(usdPrim, usdMaterialTranslationCache) {
}

std::shared_ptr<Sphere> UsdSphereReader::read() {
    auto sphere = BaseUsdImageableReader<pxr::UsdGeomSphere, Sphere>::read();

    const auto radius = UsdUtils::getAttributeValueAs<double>(usdPrim.GetRadiusAttr(), this->timeCodeToRead);
    sphere->setRadius(static_cast<float>(radius));

    return sphere;
}

std::string UsdSphereReader::getTranslatedType() {
    return "sphere";
}

} // crayg