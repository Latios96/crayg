#include "UsdMaterialReadCache.h"
#include "Logger.h"
#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include "sceneIO/read/usd/shadingnetworks/materials/UsdPreviewSurfaceReader.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/base/gf/vec3f.h>

namespace crayg {

std::shared_ptr<Material> UsdMaterialReadCache::getCachedReadPrimMaterial(const pxr::UsdSchemaBase &schemaBase) {
    return getCachedReadPrimMaterial(schemaBase.GetPrim());
}

std::shared_ptr<Material> crayg::UsdMaterialReadCache::getCachedReadPrimMaterial(const pxr::UsdPrim &prim) {
    pxr::UsdShadeMaterialBindingAPI bindingApi(prim);
    auto material = bindingApi.ComputeBoundMaterial();
    auto materialPath = material.GetPath();
    if (materialCache.find(materialPath) == materialCache.end()) {
        materialCache[materialPath] = translateMaterial(material);
    }
    return materialCache[materialPath];
}

std::shared_ptr<Material> UsdMaterialReadCache::translateMaterial(const pxr::UsdShadeMaterial &usdShadeMaterial) {
    Logger::debug("Translating material {}", usdShadeMaterial.GetPath());
    auto shader = usdShadeMaterial.ComputeSurfaceSource();

    if (!shader) {
        return getDefaultMaterial();
    }
    auto shaderId = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(shader.GetIdAttr());
    shader.GetIdAttr().Get(&shaderId);
    if (!isUsdPreviewSurface(shaderId)) {
        Logger::warning("Shader at {} is of id {}, which is not supported", shader.GetPath(), shaderId);
        return getDefaultMaterial();
    }
    UsdPreviewSurfaceReader usdPreviewSurfaceReader(shader);
    return usdPreviewSurfaceReader.read();
}

bool crayg::UsdMaterialReadCache::isUsdPreviewSurface(const pxr::TfToken &shaderId) const {
    return shaderId == pxr::TfToken("UsdPreviewSurface");
}

std::shared_ptr<Material> UsdMaterialReadCache::createDefaultMaterial() {
    return std::make_shared<UsdPreviewSurface>("defaultMaterial", Color::createGrey(0.5f));
}

UsdMaterialReadCache::UsdMaterialReadCache() {
    materialCache[pxr::SdfPath()] = createDefaultMaterial();
}

std::shared_ptr<Material> UsdMaterialReadCache::getDefaultMaterial() {
    return materialCache[pxr::SdfPath()];
}

}