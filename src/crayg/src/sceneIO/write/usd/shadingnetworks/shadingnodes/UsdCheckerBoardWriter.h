#pragma once

#include "scene/shadingnetworks/shadingnodes/CheckerBoard.h"
#include "sceneIO/write/usd/base/BaseUsdShadingNodeWriter.h"

namespace crayg {

class UsdCheckerBoardWriter : public BaseUsdShadingNodeWriter<CheckerBoard> {
  public:
    explicit UsdCheckerBoardWriter(CheckerBoard &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};
} // crayg
