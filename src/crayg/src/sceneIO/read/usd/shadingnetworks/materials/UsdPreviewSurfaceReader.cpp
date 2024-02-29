#include "UsdPreviewSurfaceReader.h"

namespace crayg {
UsdPreviewSurfaceReader::UsdPreviewSurfaceReader(const pxr::UsdShadeShader &usdPrim)
    : BaseUsdShadingNodeReader(usdPrim) {
}

std::shared_ptr<UsdPreviewSurface> UsdPreviewSurfaceReader::read() {
    auto material = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "diffuseColor", material->diffuseColor);
    UsdShadingNodeReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "emissiveColor", material->emissiveColor);
    UsdShadingNodeReadUtils::readShaderAttributeValue<bool, int>(usdPrim, "useSpecularWorkflow",
                                                                 material->useSpecularWorkflow);
    UsdShadingNodeReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "specularColor", material->specularColor);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "metallic", material->metallic);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "roughness", material->roughness);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "clearcoat", material->clearcoat);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "clearcoatRoughness", material->clearcoatRoughness);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "opacity", material->opacity);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "opacityThreshold", material->opacityThreshold);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "ior", material->ior);

    return material;
}

std::string UsdPreviewSurfaceReader::getTranslatedType() {
    return "UsdPreviewSurface";
}
} // crayg