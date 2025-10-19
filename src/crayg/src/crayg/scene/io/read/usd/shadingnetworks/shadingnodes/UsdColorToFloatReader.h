#pragma once

#include "crayg/scene/io/read/usd/base/BaseUsdShadingNodeReader.h"
#include "crayg/scene/shadingnetworks/shadingnodes/ColorToFloat.h"

namespace crayg {

class UsdColorToFloatReader : public BaseUsdShadingNodeReader<ColorToFloat> {
  public:
    UsdColorToFloatReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<ColorToFloat> read() override;

  protected:
    std::string getTranslatedType() override;
};

}