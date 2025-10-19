#pragma once

#include "scene/io/read/usd/base/BaseUsdShadingNodeReader.h"
#include "scene/shadingnetworks/shadingnodes/CheckerBoard.h"

namespace crayg {

class UsdCheckerBoardReader : public BaseUsdShadingNodeReader<CheckerBoard> {
  public:
    UsdCheckerBoardReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<CheckerBoard> read() override;

  protected:
    std::string getTranslatedType() override;
};

}
