#pragma once

#include "crayg/scene/io/write/usd/base/BaseUsdMaterialWriter.h"
#include "crayg/scene/io/write/usd/base/BaseUsdWriter.h"
#include "crayg/scene/shadingnetworks/materials/UsdPreviewSurface.h"
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

}
