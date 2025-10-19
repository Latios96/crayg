#pragma once

#include "crayg/scene/io/write/usd/base/BaseUsdShadingNodeWriter.h"
#include "crayg/scene/shadingnetworks/shadingnodes/CheckerBoard.h"

namespace crayg {

class UsdCheckerBoardWriter : public BaseUsdShadingNodeWriter<CheckerBoard> {
  public:
    explicit UsdCheckerBoardWriter(CheckerBoard &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};
}
