#include "UsdPointLightWriter.h"

namespace crayg {

UsdPointLightWriter::UsdPointLightWriter(Light &craygObject) : BaseUsdLightWriter(craygObject) {
}

pxr::UsdLuxSphereLight UsdPointLightWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdLuxSphereLight = BaseUsdLightWriter::write(stage, usdPathFactory);

    usdLuxSphereLight.GetRadiusAttr().Set(0.0f);

    return usdLuxSphereLight;
}

}