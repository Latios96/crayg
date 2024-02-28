#include "UsdMaterialWriteCache.h"
#include "Logger.h"
#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/write/usd/shadingnetworks/materials/UsdPreviewSurfaceWriter.h"

namespace crayg {

UsdMaterialWriteCache::UsdMaterialWriteCache(const pxr::UsdStagePtr &usdStagePtr, UsdPathFactory &usdPathFactory,
                                             UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : stage(usdStagePtr), usdPathFactory(usdPathFactory), usdShadingNodeWriteCache(usdShadingNodeWriteCache) {
}

pxr::UsdShadeMaterial UsdMaterialWriteCache::getCachedUsdMaterial(const std::shared_ptr<Material> material) {
    auto materialPath = material->getName();
    if (materialCache.find(materialPath) == materialCache.end()) {
        materialCache[materialPath] = translateMaterial(material);
    }
    return materialCache[materialPath];
}

pxr::UsdShadeMaterial UsdMaterialWriteCache::translateMaterial(const std::shared_ptr<Material> material) {

    if (material->getType() == "UsdPreviewSurface") {
        const auto usdPreviewSurfaceMaterial = std::static_pointer_cast<UsdPreviewSurface>(material);
        UsdPreviewSurfaceWriter usdPreviewSurfaceWriter(*usdPreviewSurfaceMaterial, usdShadingNodeWriteCache);
        return usdPreviewSurfaceWriter.write(stage, usdPathFactory);
    }

    Logger::warning("Shader {} of type {} is not supported, writing default UsdPreviewSurface instead",
                    material->getName(), material->getType());
    const pxr::SdfPath materialPath = usdPathFactory.getPathForName(material->getName(), "Material");
    auto usdShadeMaterial = pxr::UsdShadeMaterial::Define(stage, materialPath);
    auto usdPreviewSurfaceShader = createUsdPreviewSurface(usdShadeMaterial);

    return usdShadeMaterial;
}

pxr::UsdShadeShader UsdMaterialWriteCache::createUsdPreviewSurface(const pxr::UsdShadeMaterial &usdShadeMaterial) {
    auto usdShadeShader =
        pxr::UsdShadeShader::Define(stage, usdShadeMaterial.GetPath().AppendChild(pxr::TfToken("UsdPreviewSurface")));
    usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(), pxr::TfToken("surface"));
    usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
    return usdShadeShader;
}

} // crayg