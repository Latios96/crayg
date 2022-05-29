//
// Created by Jan on 21.05.2022.
//

#include "UsdSphereTranslator.h"
#include "UsdUtils.h"

namespace crayg {

UsdSphereTranslator::UsdSphereTranslator(const pxr::UsdGeomSphere &usdPrim,
                                         UsdMaterialTranslationCache &usdMaterialTranslationCache)
    : BaseUsdImageableTranslator(usdPrim, usdMaterialTranslationCache) {}

std::shared_ptr<Sphere> UsdSphereTranslator::translate() {
    auto sphere = BaseUsdImageableTranslator<pxr::UsdGeomSphere, Sphere>::translate();

    const auto radius = UsdUtils::getAttributeValueAs<double>(usdPrim.GetRadiusAttr());
    sphere->setRadius(static_cast<float>(radius));

    return sphere;
}
std::string UsdSphereTranslator::getTranslatedType() {
    return "sphere";
}

} // crayg