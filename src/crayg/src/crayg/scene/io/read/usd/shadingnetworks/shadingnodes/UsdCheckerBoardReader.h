#pragma once

#include "crayg/scene/io/read/usd/base/BaseUsdShadingNodeReader.h"
#include "crayg/scene/shadingnetworks/shadingnodes/CheckerBoard.h"

namespace crayg {

class UsdCheckerBoardReader : public BaseUsdShadingNodeReader<CheckerBoard> {
  public:
    UsdCheckerBoardReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<CheckerBoard> read() override;

  protected:
    std::string getTranslatedType() override;
};

}
