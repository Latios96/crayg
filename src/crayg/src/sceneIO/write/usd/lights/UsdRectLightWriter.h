#pragma once

#include "scene/lights/RectLight.h"
#include "sceneIO/write/usd/base/BaseUsdLightWriter.h"
#include <pxr/usd/usdLux/rectLight.h>

namespace crayg {

class UsdRectLightWriter : public BaseUsdLightWriter<pxr::UsdLuxRectLight, RectLight> {
  public:
    UsdRectLightWriter(RectLight &craygObject);

    pxr::UsdLuxRectLight write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
};

} // crayg
