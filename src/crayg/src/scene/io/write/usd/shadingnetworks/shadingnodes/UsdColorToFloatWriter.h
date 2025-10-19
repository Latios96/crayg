#pragma once

#include "scene/io/write/usd/base/BaseUsdShadingNodeWriter.h"
#include "scene/shadingnetworks/shadingnodes/ColorToFloat.h"

namespace crayg {

class UsdColorToFloatWriter : public BaseUsdShadingNodeWriter<ColorToFloat> {
  public:
    explicit UsdColorToFloatWriter(ColorToFloat &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};
}