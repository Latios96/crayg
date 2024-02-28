#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDPREVIEWSURFACEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDPREVIEWSURFACEWRITER_H_

#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include "sceneIO/write/usd/base/BaseUsdMaterialWriter.h"
#include "sceneIO/write/usd/base/BaseUsdWriter.h"
#include <pxr/usd/usdShade/material.h>

namespace crayg {

class UsdPreviewSurfaceWriter : public BaseUsdMaterialWriter<UsdPreviewSurface> {
  public:
    explicit UsdPreviewSurfaceWriter(UsdPreviewSurface &craygObject,
                                     UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeMaterial write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDPREVIEWSURFACEWRITER_H_
