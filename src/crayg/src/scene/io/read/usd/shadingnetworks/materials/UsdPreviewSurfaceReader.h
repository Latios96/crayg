#pragma once

#include "scene/io/read/usd/base/BaseUsdShadingNodeReader.h"
#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"

namespace crayg {

class UsdPreviewSurfaceReader : public BaseUsdShadingNodeReader<UsdPreviewSurface> {
  public:
    explicit UsdPreviewSurfaceReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &shadingNodeReadCache);

    std::shared_ptr<UsdPreviewSurface> read() override;

  protected:
    std::string getTranslatedType() override;
};

}
