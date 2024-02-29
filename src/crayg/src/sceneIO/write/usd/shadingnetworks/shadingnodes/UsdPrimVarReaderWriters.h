#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_SHADINGNETWORKS_SHADINGNODES_PRIMVARREADERWRITERS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_SHADINGNETWORKS_SHADINGNODES_PRIMVARREADERWRITERS_H_

#include "scene/shadingnetworks/shadingnodes/PrimVarReaders.h"
#include "sceneIO/write/usd/base/BaseUsdShadingNodeWriter.h"

namespace crayg {

class UsdPrimVarReaderVector2fWriter : public BaseUsdShadingNodeWriter<PrimVarReaderVector2f> {
  public:
    UsdPrimVarReaderVector2fWriter(PrimVarReaderVector2f &craygObject,
                                   UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_SHADINGNETWORKS_SHADINGNODES_PRIMVARREADERWRITERS_H_
