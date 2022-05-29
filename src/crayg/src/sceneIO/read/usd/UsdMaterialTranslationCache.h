//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDMATERIALTRANSLATIONCACHE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDMATERIALTRANSLATIONCACHE_H_

#include "scene/Material.h"
#include "CraygUsdBase.h"
#include <pxr/usd/usdShade/materialBindingAPI.h>
#include <pxr/usd/usd/schemaBase.h>

namespace crayg {

class UsdMaterialTranslationCache {
 public:
    std::shared_ptr<Material> getTranslatedPrimMaterial(const pxr::UsdPrim &prim);
    std::shared_ptr<Material> getTranslatedPrimMaterial(const pxr::UsdSchemaBase &schemaBase);
    UsdMaterialTranslationCache();
 private:
    bool isUsdPreviewSurface(const pxr::TfToken &shaderId) const;
    std::shared_ptr<Material> translateMaterial(const pxr::UsdShadeMaterial &usdShadeMaterial);
    std::shared_ptr<Material> createDefaultMaterial();
    std::shared_ptr<Material> getDefaultMaterial();

    std::map<pxr::SdfPath, std::shared_ptr<Material>> materialCache;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDMATERIALTRANSLATIONCACHE_H_
