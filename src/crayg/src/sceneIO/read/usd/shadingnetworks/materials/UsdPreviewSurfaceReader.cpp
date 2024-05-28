#include "UsdPreviewSurfaceReader.h"
#include "scene/shadingnetworks/shadingnodes/CheckerBoard.h"
#include "sceneIO/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h"

namespace crayg {
UsdPreviewSurfaceReader::UsdPreviewSurfaceReader(const pxr::UsdShadeShader &usdPrim,
                                                 UsdShadingNodeReadCache &shadingNodeReadCache)
    : BaseUsdShadingNodeReader(usdPrim, shadingNodeReadCache) {
}

std::shared_ptr<UsdPreviewSurface> UsdPreviewSurfaceReader::read() {
    auto material = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "diffuseColor", material->diffuseColor,
                                                                  usdShadingNodeReadCache);

    UsdShadingNodeReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "emissiveColor", material->emissiveColor,
                                                                  usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderAttributeValue<bool, int>(usdPrim, "useSpecularWorkflow",
                                                                 material->useSpecularWorkflow);
    UsdShadingNodeReadUtils::readShaderAttributeValue<Color, pxr::GfVec3f>(usdPrim, "specularColor",
                                                                           material->specularColor.value);
    UsdShadingNodeReadUtils::readShaderAttributeValue<float, float>(usdPrim, "metallic", material->metallic.value);
    UsdShadingNodeReadUtils::readShaderAttributeValue<float, float>(usdPrim, "metallic", material->metallic.value);
    UsdShadingNodeReadUtils::readShaderAttributeValue<float, float>(usdPrim, "roughness", material->roughness.value);
    UsdShadingNodeReadUtils::readShaderAttributeValue<float, float>(usdPrim, "clearcoat", material->clearcoat.value);
    UsdShadingNodeReadUtils::readShaderAttributeValue<float, float>(usdPrim, "clearcoatRoughness",
                                                                    material->clearcoatRoughness.value);
    UsdShadingNodeReadUtils::readShaderAttributeValue<float, float>(usdPrim, "opacity", material->opacity.value);
    UsdShadingNodeReadUtils::readShaderAttributeValue<float, float>(usdPrim, "opacityThreshold",
                                                                    material->opacityThreshold.value);
    UsdShadingNodeReadUtils::readShaderAttributeValue<float, float>(usdPrim, "ior", material->ior.value);

    return material;
}

std::string UsdPreviewSurfaceReader::getTranslatedType() {
    return "UsdPreviewSurface";
}
} // crayg