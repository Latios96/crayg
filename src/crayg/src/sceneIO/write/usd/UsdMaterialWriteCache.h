#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDMATERIALWRITECACHE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDMATERIALWRITECACHE_H_

#include <map>
#include "scene/Material.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "UsdPathFactory.h"
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
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDMATERIALWRITECACHE_H_
