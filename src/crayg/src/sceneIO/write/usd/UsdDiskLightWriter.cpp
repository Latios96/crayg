//
// Created by Jan on 03.06.2022.
//

#include "UsdDiskLightWriter.h"

namespace crayg {

UsdDiskLightWriter::UsdDiskLightWriter(const std::shared_ptr<DiskLight> &craygObject)
    : BaseUsdLightWriter(craygObject) {}

pxr::UsdLuxDiskLight UsdDiskLightWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdLuxDiskLight = BaseUsdLightWriter::write(stage, usdPathFactory);

    usdLuxDiskLight.GetRadiusAttr().Set(this->craygObject->getRadius());

    return usdLuxDiskLight;
}
} // crayg