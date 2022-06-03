//
// Created by Jan on 03.06.2022.
//

#include "UsdPointLightWriter.h"

namespace crayg {

UsdPointLightWriter::UsdPointLightWriter(const std::shared_ptr<Light> &craygObject) : BaseUsdLightWriter(craygObject) {}

pxr::UsdLuxSphereLight UsdPointLightWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdLuxSphereLight = BaseUsdLightWriter::write(stage, usdPathFactory);

    usdLuxSphereLight.GetRadiusAttr().Set(0);

    return usdLuxSphereLight;
}

} // crayg