#pragma once

#include "crayg/scene/io/write/usd/base/BaseUsdShadingNodeWriter.h"
#include "crayg/scene/shadingnetworks/shadingnodes/PrimVarReaders.h"

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

}
