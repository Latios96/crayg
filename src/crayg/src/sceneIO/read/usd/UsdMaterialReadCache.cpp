#include "UsdMaterialReadCache.h"
#include "sceneIO/usd/UsdUtils.h"
#include "Logger.h"
#include "scene/materials/UsdPreviewSurface.h"
#include "sceneIO/usd/UsdConversions.h"
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
    auto shaderId = UsdUtils::getAttributeValueAs<pxr::TfToken>(shader.GetIdAttr());
    shader.GetIdAttr().Get(&shaderId);
    if (!isUsdPreviewSurface(shaderId)) {
        Logger::warning("Shader at {} is of id {}, which is not supported",
                        shader.GetPath(),
                        shaderId);
        return getDefaultMaterial();
    }

    auto material = std::make_shared<UsdPreviewSurface>(usdShadeMaterial.GetPath().GetString());

    readShaderAttributeValue<Color, pxr::GfVec3f>(shader, "diffuseColor", material->diffuseColor);
    readShaderAttributeValue<Color, pxr::GfVec3f>(shader, "emissiveColor", material->emissiveColor);
    readShaderAttributeValue<bool, int>(shader, "useSpecularWorkflow", material->useSpecularWorkflow);
    readShaderAttributeValue<Color, pxr::GfVec3f>(shader, "specularColor", material->specularColor);
    readShaderAttributeValue<float, float>(shader, "metallic", material->metallic);
    readShaderAttributeValue<float, float>(shader, "roughness", material->roughness);
    readShaderAttributeValue<float, float>(shader, "clearcoat", material->clearcoat);
    readShaderAttributeValue<float, float>(shader, "clearcoatRoughness", material->clearcoatRoughness);
    readShaderAttributeValue<float, float>(shader, "opacity", material->opacity);
    readShaderAttributeValue<float, float>(shader, "opacityThreshold", material->opacityThreshold);
    readShaderAttributeValue<float, float>(shader, "ior", material->ior);

    return material;
}

bool crayg::UsdMaterialReadCache::isUsdPreviewSurface(const pxr::TfToken &shaderId) const {
    return shaderId == pxr::TfToken("UsdPreviewSurface");
}
std::shared_ptr<Material> UsdMaterialReadCache::createDefaultMaterial() {
    return std::make_shared<UsdPreviewSurface>("defaultMaterial",
                                               Color::createGrey(0.5f));
}
UsdMaterialReadCache::UsdMaterialReadCache() {
    materialCache[pxr::SdfPath()] = createDefaultMaterial();
}
std::shared_ptr<Material> UsdMaterialReadCache::getDefaultMaterial() {
    return materialCache[pxr::SdfPath()];
}

template<>
Color UsdMaterialReadCache::readValue<Color, pxr::GfVec3f>(const pxr::UsdShadeInput &input) {
    auto value = UsdUtils::getAttributeValueAs<pxr::GfVec3f>(input);
    return UsdConversions::convertColor(value);
}

template<>
bool UsdMaterialReadCache::readValue<bool, int>(const pxr::UsdShadeInput &input) {
    auto value = UsdUtils::getAttributeValueAs<int>(input);
    return value != 0;
}

template<>
float UsdMaterialReadCache::readValue<float, float>(const pxr::UsdShadeInput &input) {
    return UsdUtils::getAttributeValueAs<float>(input);
}

}