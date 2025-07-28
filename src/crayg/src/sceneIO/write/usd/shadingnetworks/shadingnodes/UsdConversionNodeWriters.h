#pragma once

#include "scene/shadingnetworks/shadingnodes/ConversionNodes.h"
#include "sceneIO/write/usd/base/BaseUsdShadingNodeWriter.h"

namespace crayg {

class UsdVector2fToColorWriter : public BaseUsdShadingNodeWriter<Vector2fToColor> {
  public:
    UsdVector2fToColorWriter(Vector2fToColor &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};
}
