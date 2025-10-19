#include "UsdDiskLightWriter.h"

namespace crayg {

UsdDiskLightWriter::UsdDiskLightWriter(DiskLight &craygObject) : BaseUsdLightWriter(craygObject) {
}

pxr::UsdLuxDiskLight UsdDiskLightWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdLuxDiskLight = BaseUsdLightWriter::write(stage, usdPathFactory);

    usdLuxDiskLight.GetRadiusAttr().Set(this->craygObject.getRadius());

    return usdLuxDiskLight;
}
}