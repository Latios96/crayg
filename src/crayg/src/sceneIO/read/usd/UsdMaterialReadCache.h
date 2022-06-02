//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDMATERIALREADCACHE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDMATERIALREADCACHE_H_

#include "scene/Material.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/usd/usdShade/materialBindingAPI.h>
#include <pxr/usd/usd/schemaBase.h>

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
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDMATERIALREADCACHE_H_
