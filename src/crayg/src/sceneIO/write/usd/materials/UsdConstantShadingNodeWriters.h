#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDCONSTANTSHADINGNODEWRITERS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDCONSTANTSHADINGNODEWRITERS_H_

#include "scene/materials/ConstantShadingNodes.h"
#include "sceneIO/write/usd/base/BaseUsdShadingNodeWriter.h"

namespace crayg {

class UsdFloatConstantWriter : public BaseUsdShadingNodeWriter<FloatConstant> {
  public:
    explicit UsdFloatConstantWriter(FloatConstant &craygObject);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDCONSTANTSHADINGNODEWRITERS_H_
