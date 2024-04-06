#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_SHADINGNETWORKS_SHADINGNODES_USDCHECKERBOARDWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_SHADINGNETWORKS_SHADINGNODES_USDCHECKERBOARDWRITER_H_

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

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_SHADINGNETWORKS_SHADINGNODES_USDCHECKERBOARDWRITER_H_
