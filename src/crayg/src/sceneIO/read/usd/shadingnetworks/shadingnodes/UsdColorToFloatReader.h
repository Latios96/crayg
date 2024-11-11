#pragma once

#include "scene/shadingnetworks/shadingnodes/ColorToFloat.h"
#include "sceneIO/read/usd/base/BaseUsdShadingNodeReader.h"

namespace crayg {

class UsdColorToFloatReader : public BaseUsdShadingNodeReader<ColorToFloat> {
  public:
    UsdColorToFloatReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<ColorToFloat> read() override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg