#pragma once

#include "scene/io/read/usd/base/BaseUsdShadingNodeReader.h"
#include "scene/shadingnetworks/shadingnodes/ConversionNodes.h"

namespace crayg {

class UsdVector2fToColorReader : public BaseUsdShadingNodeReader<Vector2fToColor> {
  public:
    explicit UsdVector2fToColorReader(const pxr::UsdShadeShader &usdPrim,
                                      UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<Vector2fToColor> read() override;

  protected:
    std::string getTranslatedType() override;
};

}
