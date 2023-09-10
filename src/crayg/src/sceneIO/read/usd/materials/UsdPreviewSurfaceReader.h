#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_MATERIALS_USDPREVIEWSURFACEREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_MATERIALS_USDPREVIEWSURFACEREADER_H_

#include "scene/materials/UsdPreviewSurface.h"
#include "sceneIO/read/usd/base/BaseUsdMaterialReader.h"

namespace crayg {

class UsdPreviewSurfaceReader : public BaseUsdMaterialReader<UsdPreviewSurface> {
  public:
    explicit UsdPreviewSurfaceReader(const pxr::UsdShadeShader &usdPrim);

    std::shared_ptr<UsdPreviewSurface> read() override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_MATERIALS_USDPREVIEWSURFACEREADER_H_
