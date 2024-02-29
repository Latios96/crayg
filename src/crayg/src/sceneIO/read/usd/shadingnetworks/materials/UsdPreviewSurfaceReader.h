#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_MATERIALS_USDPREVIEWSURFACEREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_MATERIALS_USDPREVIEWSURFACEREADER_H_

#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include "sceneIO/read/usd/base/BaseUsdShadingNodeReader.h"

namespace crayg {

class UsdPreviewSurfaceReader : public BaseUsdShadingNodeReader<UsdPreviewSurface> {
  public:
    explicit UsdPreviewSurfaceReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &shadingNodeReadCache);

    std::shared_ptr<UsdPreviewSurface> read() override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_MATERIALS_USDPREVIEWSURFACEREADER_H_
