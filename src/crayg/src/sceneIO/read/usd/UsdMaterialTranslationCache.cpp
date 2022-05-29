//
// Created by Jan on 21.05.2022.
//

#include "UsdMaterialTranslationCache.h"
#include "UsdUtils.h"
#include "Logger.h"
#include "scene/DiffuseMaterial.h"
#include "UsdConversions.h"
#include <pxr/base/gf/vec3f.h>

namespace crayg {

std::shared_ptr<Material> UsdMaterialTranslationCache::getTranslatedPrimMaterial(const pxr::UsdSchemaBase &schemaBase) {
    return getTranslatedPrimMaterial(schemaBase.GetPrim());
}

std::shared_ptr<Material> crayg::UsdMaterialTranslationCache::getTranslatedPrimMaterial(const pxr::UsdPrim &prim) {
    pxr::UsdShadeMaterialBindingAPI bindingApi(prim);
    auto material = bindingApi.ComputeBoundMaterial();
    auto materialPath = material.GetPath();
    if (materialCache.find(materialPath) == materialCache.end()) {
        materialCache[materialPath] = translateMaterial(material);
    }
    return materialCache[materialPath];
}

std::shared_ptr<Material> UsdMaterialTranslationCache::translateMaterial(const pxr::UsdShadeMaterial &usdShadeMaterial) {
    Logger::info("Translating material {}", usdShadeMaterial.GetPath().GetString());
    auto shader = usdShadeMaterial.ComputeSurfaceSource();

    if (!shader) {
        return getDefaultMaterial();
    }
    auto shaderId = UsdUtils::getAttributeValueAs<pxr::TfToken>(shader.GetIdAttr());
    shader.GetIdAttr().Get(&shaderId);
    if (!isUsdPreviewSurface(shaderId)) {
        Logger::warning("Shader at {} is of id {}, which is not supported",
                        shader.GetPath().GetString(),
                        shaderId.GetString());
        return getDefaultMaterial();
    }

    Color color(0.18, 0.18, 0.18);
    auto diffuseColorInput = shader.GetInput(pxr::TfToken("diffuseColor"));
    if (diffuseColorInput) {
        auto usdColor = UsdUtils::getAttributeValueAs<pxr::GfVec3f>(diffuseColorInput);
        color = UsdConversions::convertColor(usdColor);
    }

    auto material = std::make_shared<DiffuseMaterial>(usdShadeMaterial.GetPath().GetString(), color);
    return material;
}

bool crayg::UsdMaterialTranslationCache::isUsdPreviewSurface(const pxr::TfToken &shaderId) const {
    return shaderId == pxr::TfToken("UsdPreviewSurface");
}
std::shared_ptr<Material> UsdMaterialTranslationCache::createDefaultMaterial() {
    return std::make_shared<DiffuseMaterial>("defaultMaterial",
                                             Color(1, 0, 0));
}
UsdMaterialTranslationCache::UsdMaterialTranslationCache() {
    materialCache[pxr::SdfPath()] = createDefaultMaterial();
}
std::shared_ptr<Material> UsdMaterialTranslationCache::getDefaultMaterial() {
    return materialCache[pxr::SdfPath()];
}

}