#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDMATERIALREADCACHE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDMATERIALREADCACHE_H_

#include "scene/Material.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/usd/UsdConversions.h"
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

    template<typename T, typename UsdType>
    void readShaderAttributeValue(const pxr::UsdShadeShader &shader, const std::string &attributeName, T &target);

    template<typename T, typename UsdType>
    T readValue(const pxr::UsdShadeInput &input);

    std::map<pxr::SdfPath, std::shared_ptr<Material>> materialCache;
};

template<typename T, typename UsdType>
void UsdMaterialReadCache::readShaderAttributeValue(const pxr::UsdShadeShader &shader,
                                                    const std::string &attributeName,
                                                    T &target) {
    auto input = shader.GetInput(pxr::TfToken(attributeName));

    if (!input || input.HasConnectedSource()) {
        return;
    }

    target = readValue<T, UsdType>(input);

}
template<typename T, typename UsdType>
T UsdMaterialReadCache::readValue(const pxr::UsdShadeInput &input) {
    auto value = UsdUtils::getAttributeValueAs<UsdType>(input);
    return UsdConversions::convert(value);
}

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDMATERIALREADCACHE_H_
