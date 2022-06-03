//
// Created by Jan on 03.06.2022.
//

#include "UsdRectLightWriter.h"

namespace crayg {

UsdRectLightWriter::UsdRectLightWriter(const std::shared_ptr<RectLight> &craygObject)
    : BaseUsdLightWriter(craygObject) {}

pxr::UsdLuxRectLight UsdRectLightWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdLuxRectLight = BaseUsdLightWriter::write(stage, usdPathFactory);

    usdLuxRectLight.GetHeightAttr().Set(this->craygObject->getHeight());
    usdLuxRectLight.GetWidthAttr().Set(this->craygObject->getWidth());

    return usdLuxRectLight;
}

} // crayg