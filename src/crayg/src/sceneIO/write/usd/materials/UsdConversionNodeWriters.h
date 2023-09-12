#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDCONVERSIONNODEWRITERS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDCONVERSIONNODEWRITERS_H_

#include "scene/materials/ConversionNodes.h"
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
} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDCONVERSIONNODEWRITERS_H_
