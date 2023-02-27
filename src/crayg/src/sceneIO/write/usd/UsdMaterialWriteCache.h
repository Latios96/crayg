#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDMATERIALWRITECACHE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDMATERIALWRITECACHE_H_

#include "UsdPathFactory.h"
#include "scene/materials/Material.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <map>
#include <pxr/usd/usdShade/materialBindingAPI.h>

namespace crayg {

class UsdMaterialWriteCache {
  public:
    UsdMaterialWriteCache(const pxr::UsdStagePtr &usdStagePtr, UsdPathFactory &usdPathFactory);
    pxr::UsdShadeMaterial getCachedUsdMaterial(const std::shared_ptr<Material> material);

  private:
    pxr::UsdShadeMaterial translateMaterial(const std::shared_ptr<Material> material);
    std::map<std::string, pxr::UsdShadeMaterial> materialCache;
    pxr::UsdStagePtr stage;
    UsdPathFactory &usdPathFactory;
    pxr::UsdShadeShader createUsdPreviewSurface(const pxr::UsdShadeMaterial &usdShadeMaterial);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDMATERIALWRITECACHE_H_
