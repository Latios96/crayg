#include "UsdPreviewSurfaceReader.h"

namespace crayg {
UsdPreviewSurfaceReader::UsdPreviewSurfaceReader(const pxr::UsdShadeShader &usdPrim) : BaseUsdMaterialReader(usdPrim) {
}

std::shared_ptr<UsdPreviewSurface> UsdPreviewSurfaceReader::read() {
    auto material = BaseUsdMaterialReader::read();

    UsdMaterialReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "diffuseColor", material->diffuseColor);
    UsdMaterialReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "emissiveColor", material->emissiveColor);
    UsdMaterialReadUtils::readShaderAttributeValue<bool, int>(usdPrim, "useSpecularWorkflow",
                                                              material->useSpecularWorkflow);
    UsdMaterialReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "specularColor", material->specularColor);
    UsdMaterialReadUtils::readShaderInput<float, float>(usdPrim, "metallic", material->metallic);
    UsdMaterialReadUtils::readShaderInput<float, float>(usdPrim, "roughness", material->roughness);
    UsdMaterialReadUtils::readShaderInput<float, float>(usdPrim, "clearcoat", material->clearcoat);
    UsdMaterialReadUtils::readShaderInput<float, float>(usdPrim, "clearcoatRoughness", material->clearcoatRoughness);
    UsdMaterialReadUtils::readShaderInput<float, float>(usdPrim, "opacity", material->opacity);
    UsdMaterialReadUtils::readShaderInput<float, float>(usdPrim, "opacityThreshold", material->opacityThreshold);
    UsdMaterialReadUtils::readShaderInput<float, float>(usdPrim, "ior", material->ior);

    return material;
}

std::string UsdPreviewSurfaceReader::getTranslatedType() {
    return "UsdPreviewSurface";
}
} // crayg