#include "UsdPreviewSurfaceReader.h"

namespace crayg {
UsdPreviewSurfaceReader::UsdPreviewSurfaceReader(const pxr::UsdShadeShader &usdPrim) : BaseUsdMaterialReader(usdPrim) {
}

std::shared_ptr<UsdPreviewSurface> UsdPreviewSurfaceReader::read() {
    auto material = BaseUsdMaterialReader::read();

    UsdMaterialReadUtils::readShaderAttributeValue<Color, pxr::GfVec3f>(usdPrim, "diffuseColor",
                                                                        material->diffuseColor);
    UsdMaterialReadUtils::readShaderAttributeValue<Color, pxr::GfVec3f>(usdPrim, "emissiveColor",
                                                                        material->emissiveColor);
    UsdMaterialReadUtils::readShaderAttributeValue<bool, int>(usdPrim, "useSpecularWorkflow",
                                                              material->useSpecularWorkflow);
    UsdMaterialReadUtils::readShaderAttributeValue<Color, pxr::GfVec3f>(usdPrim, "specularColor",
                                                                        material->specularColor);
    UsdMaterialReadUtils::readShaderAttributeValue<float, float>(usdPrim, "metallic", material->metallic);
    UsdMaterialReadUtils::readShaderAttributeValue<float, float>(usdPrim, "roughness", material->roughness);
    UsdMaterialReadUtils::readShaderAttributeValue<float, float>(usdPrim, "clearcoat", material->clearcoat);
    UsdMaterialReadUtils::readShaderAttributeValue<float, float>(usdPrim, "clearcoatRoughness",
                                                                 material->clearcoatRoughness);
    UsdMaterialReadUtils::readShaderAttributeValue<float, float>(usdPrim, "opacity", material->opacity);
    UsdMaterialReadUtils::readShaderAttributeValue<float, float>(usdPrim, "opacityThreshold",
                                                                 material->opacityThreshold);
    UsdMaterialReadUtils::readShaderAttributeValue<float, float>(usdPrim, "ior", material->ior);

    return material;
}

std::string UsdPreviewSurfaceReader::getTranslatedType() {
    return "UsdPreviewSurface";
}
} // crayg