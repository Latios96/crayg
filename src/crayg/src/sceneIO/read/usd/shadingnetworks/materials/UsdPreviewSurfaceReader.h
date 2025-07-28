#pragma once

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

}
