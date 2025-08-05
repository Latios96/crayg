#pragma once

#include "UsdShadingNodeWriteCache.h"
#include "scene/shadingnetworks/materials/Material.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include <map>
#include <pxr/usd/usdShade/materialBindingAPI.h>

namespace crayg {

class UsdMaterialWriteCache {
  public:
    UsdMaterialWriteCache(const pxr::UsdStagePtr &usdStagePtr, UsdPathFactory &usdPathFactory,
                          UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeMaterial getCachedUsdMaterial(const std::shared_ptr<Material> material);

  private:
    pxr::UsdShadeMaterial translateMaterial(const std::shared_ptr<Material> material);
    std::map<std::string, pxr::UsdShadeMaterial> materialCache;
    pxr::UsdStagePtr stage;
    UsdPathFactory &usdPathFactory;
    pxr::UsdShadeShader createUsdPreviewSurface(const pxr::UsdShadeMaterial &usdShadeMaterial);
    UsdShadingNodeWriteCache &usdShadingNodeWriteCache;
};

}
