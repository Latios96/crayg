#pragma once

#include "scene/lights/RectLight.h"
#include "sceneIO/read/usd/base/BaseUsdLightReader.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/usd/usdLux/rectLight.h>

namespace crayg {

class UsdRectLightReader : public BaseUsdLightReader<pxr::UsdLuxRectLight, RectLight> {
  public:
    UsdRectLightReader(const pxr::UsdLuxRectLight &rectLight);
    std::shared_ptr<RectLight> read() override;

  protected:
    std::string getTranslatedType() override;
};

}
