#include "UsdPreviewSurfaceWriter.h"
#include "scene/io/usd/UsdConversions.h"

namespace crayg {

UsdPreviewSurfaceWriter::UsdPreviewSurfaceWriter(UsdPreviewSurface &craygObject,
                                                 UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : BaseUsdMaterialWriter(craygObject, usdShadingNodeWriteCache) {
}

std::string UsdPreviewSurfaceWriter::getTranslatedType() {
    return "UsdPreviewSurface";
}

pxr::UsdShadeMaterial UsdPreviewSurfaceWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdPreviewSurfaceMaterial = BaseUsdMaterialWriter::write(stage, usdPathFactory);
    auto usdPreviewSurfaceShader = usdPreviewSurfaceMaterial.ComputeSurfaceSource();

    usdPreviewSurfaceShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));

    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdPreviewSurfaceShader, "diffuseColor",
                                                            craygObject.diffuseColor);
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdPreviewSurfaceShader, "emissiveColor",
                                                            craygObject.emissiveColor);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("useSpecularWorkflow"), pxr::SdfValueTypeNames->Int)
        .Set(craygObject.useSpecularWorkflow == true ? 1 : 0);
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdPreviewSurfaceShader, "specularColor",
                                                            craygObject.specularColor);
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdPreviewSurfaceShader, "metallic", craygObject.metallic);

    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdPreviewSurfaceShader, "roughness",
                                                            craygObject.roughness);
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdPreviewSurfaceShader, "clearcoat",
                                                            craygObject.clearcoat);
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdPreviewSurfaceShader, "clearcoatRoughness",
                                                            craygObject.clearcoatRoughness);
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdPreviewSurfaceShader, "opacity", craygObject.opacity);
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdPreviewSurfaceShader, "opacityThreshold",
                                                            craygObject.opacityThreshold);
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdPreviewSurfaceShader, "ior", craygObject.ior);

    return usdPreviewSurfaceMaterial;
}

}