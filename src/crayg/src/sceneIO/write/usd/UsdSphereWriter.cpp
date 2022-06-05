//
// Created by Jan on 03.06.2022.
//

#include "UsdSphereWriter.h"

namespace crayg {

UsdSphereWriter::UsdSphereWriter(const std::shared_ptr<Sphere> &craygObject,
                                 UsdMaterialWriteCache &usdMaterialWriteCache) : BaseUsdSceneObjectWriter(craygObject,
                                                                                                          usdMaterialWriteCache) {}

pxr::UsdGeomSphere UsdSphereWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdGeomSphere = BaseUsdSceneObjectWriter::write(stage, usdPathFactory);

    usdGeomSphere.GetRadiusAttr().Set(static_cast<double>(this->craygObject->getRadius()));

    return usdGeomSphere;
}
} // crayg