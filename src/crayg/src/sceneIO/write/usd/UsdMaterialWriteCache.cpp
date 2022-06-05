//
// Created by Jan on 05.06.2022.
//

#include "UsdMaterialWriteCache.h"
#include "sceneIO/usd/UsdConversions.h"

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
    auto usdShadeMaterial = pxr::UsdShadeMaterial::Define(stage, materialPath);
    auto usdShadeShader =
        pxr::UsdShadeShader::Define(stage, materialPath.AppendChild(pxr::TfToken("usdPreviewSurface")));

    usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
    usdShadeShader.CreateInput(pxr::TfToken("diffuseColor"),
                               pxr::SdfValueTypeNames->Color3f).Set(UsdConversions::convert(material->getDiffuseColor()));
    usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                           pxr::TfToken("surface"));

    return usdShadeMaterial;
}

} // crayg