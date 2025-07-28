#pragma once

#include "scene/shadingnetworks/shadingnodes/CheckerBoard.h"
#include "sceneIO/read/usd/base/BaseUsdShadingNodeReader.h"

namespace crayg {

class UsdCheckerBoardReader : public BaseUsdShadingNodeReader<CheckerBoard> {
  public:
    UsdCheckerBoardReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<CheckerBoard> read() override;

  protected:
    std::string getTranslatedType() override;
};

}
