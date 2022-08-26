#include "UsdMaterialWriteCache.h"
#include "sceneIO/usd/UsdConversions.h"
#include "Logger.h"

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

    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("diffuseColor"),
                                        pxr::SdfValueTypeNames->Color3f).Set(UsdConversions::convert(material->getDiffuseColor()));

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