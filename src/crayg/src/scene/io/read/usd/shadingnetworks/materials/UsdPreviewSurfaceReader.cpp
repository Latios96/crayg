#include "UsdPreviewSurfaceReader.h"
#include "scene/io/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h"
#include "scene/shadingnetworks/shadingnodes/CheckerBoard.h"

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
    UsdShadingNodeReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "specularColor", material->specularColor,
                                                                  usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "metallic", material->metallic,
                                                           usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "roughness", material->roughness,
                                                           usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "clearcoat", material->clearcoat,
                                                           usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "clearcoatRoughness", material->clearcoatRoughness,
                                                           usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "opacity", material->opacity,
                                                           usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "opacityThreshold", material->opacityThreshold,
                                                           usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderInput<float, float>(usdPrim, "ior", material->ior, usdShadingNodeReadCache);

    return material;
}

std::string UsdPreviewSurfaceReader::getTranslatedType() {
    return "UsdPreviewSurface";
}
}