#include "UsdMaterialWriteCache.h"
#include "sceneIO/usd/UsdConversions.h"
#include "Logger.h"
#include "scene/materials/UsdPreviewSurface.h"

namespace crayg {

UsdMaterialWriteCache::UsdMaterialWriteCache(const pxr::UsdStagePtr &usdStagePtr, UsdPathFactory &usdPathFactory)
    : stage(usdStagePtr), usdPathFactory(usdPathFactory) {}

pxr::UsdShadeMaterial UsdMaterialWriteCache::getCachedUsdMaterial(const std::shared_ptr<Material> material) {
    auto materialPath = material->getName();
    if (materialCache.find(materialPath) == materialCache.end()) {
        materialCache[materialPath] = translateMaterial(material);
    }
    return materialCache[materialPath];
}

pxr::UsdShadeMaterial UsdMaterialWriteCache::translateMaterial(const std::shared_ptr<Material> material) {
    const pxr::SdfPath materialPath = usdPathFactory.getPathForName(material->getName(), "Material");
    Logger::info("Writing material {}", materialPath);

    auto usdShadeMaterial = pxr::UsdShadeMaterial::Define(stage, materialPath);
    auto usdPreviewSurfaceShader = createUsdPreviewSurface(usdShadeMaterial);

    if (material->getType() != "UsdPreviewSurface") {
        Logger::warning("Shader {} of type {} is not supported, writing default UsdPreviewSurface instead",
                        material->getName(), material->getType());
        return usdShadeMaterial;
    }
    const auto usdPreviewSurfaceMaterial = std::static_pointer_cast<UsdPreviewSurface>(material);

    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("diffuseColor"),
                     pxr::SdfValueTypeNames->Color3f)
        .Set(UsdConversions::convert(usdPreviewSurfaceMaterial->diffuseColor));
    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("emissiveColor"),
                     pxr::SdfValueTypeNames->Color3f)
        .Set(UsdConversions::convert(usdPreviewSurfaceMaterial->emissiveColor));
    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("useSpecularWorkflow"),
                     pxr::SdfValueTypeNames->Int)
        .Set(usdPreviewSurfaceMaterial->useSpecularWorkflow == true ? 1 : 0);
    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("specularColor"),
                     pxr::SdfValueTypeNames->Color3f)
        .Set(UsdConversions::convert(usdPreviewSurfaceMaterial->specularColor));
    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("metallic"),
                     pxr::SdfValueTypeNames->Float)
        .Set(usdPreviewSurfaceMaterial->metallic);
    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("roughness"),
                     pxr::SdfValueTypeNames->Float)
        .Set(usdPreviewSurfaceMaterial->roughness);
    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("clearcoat"),
                     pxr::SdfValueTypeNames->Float)
        .Set(usdPreviewSurfaceMaterial->clearcoat);
    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("clearcoatRoughness"),
                     pxr::SdfValueTypeNames->Float)
        .Set(usdPreviewSurfaceMaterial->clearcoatRoughness);
    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("opacity"),
                     pxr::SdfValueTypeNames->Float)
        .Set(usdPreviewSurfaceMaterial->opacity);
    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("opacityThreshold"),
                     pxr::SdfValueTypeNames->Float)
        .Set(usdPreviewSurfaceMaterial->opacityThreshold);
    usdPreviewSurfaceShader
        .CreateInput(pxr::TfToken("ior"),
                     pxr::SdfValueTypeNames->Float)
        .Set(usdPreviewSurfaceMaterial->ior);

    return usdShadeMaterial;
}
pxr::UsdShadeShader UsdMaterialWriteCache::createUsdPreviewSurface(const pxr::UsdShadeMaterial &usdShadeMaterial) {
    auto usdShadeShader =
        pxr::UsdShadeShader::Define(stage, usdShadeMaterial.GetPath().AppendChild(pxr::TfToken("usdPreviewSurface")));

    usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
    usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                           pxr::TfToken("surface"));
    return usdShadeShader;
}

} // crayg