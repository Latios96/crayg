#pragma once

#include "UsdShadingNodeReadCache.h"
#include "scene/shadingnetworks/materials/Material.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usd/schemaBase.h>
#include <pxr/usd/usdShade/materialBindingAPI.h>

namespace crayg {

class UsdMaterialReadCache {
  public:
    std::shared_ptr<Material> getCachedReadPrimMaterial(const pxr::UsdPrim &prim);
    std::shared_ptr<Material> getCachedReadPrimMaterial(const pxr::UsdSchemaBase &schemaBase);
    UsdMaterialReadCache();

  private:
    bool isUsdPreviewSurface(const pxr::TfToken &shaderId) const;
    std::shared_ptr<Material> translateMaterial(const pxr::UsdShadeMaterial &usdShadeMaterial);
    std::shared_ptr<Material> createDefaultMaterial();
    std::shared_ptr<Material> getDefaultMaterial();

    std::map<pxr::SdfPath, std::shared_ptr<Material>> materialCache;
    pxr::UsdTimeCode timeCodeToRead = pxr::UsdTimeCode::EarliestTime();
    UsdShadingNodeReadCache usdShadingNodeReadCache;
};

}
