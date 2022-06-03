//
// Created by Jan on 03.06.2022.
//

#include "UsdSphereWriter.h"

namespace crayg {
UsdSphereWriter::UsdSphereWriter(const std::shared_ptr<Sphere> &craygObject)
    : BaseUsdTransformableWriter(craygObject) {}

pxr::UsdGeomSphere UsdSphereWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdGeomSphere = BaseUsdTransformableWriter::write(stage, usdPathFactory);

    usdGeomSphere.GetRadiusAttr().Set(static_cast<double>(this->craygObject->getRadius()));

    return usdGeomSphere;
}

std::string UsdSphereWriter::getTranslatedType() {
    return "sphere";
}
} // crayg