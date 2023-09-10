#include "UsdPreviewSurfaceWriter.h"
#include "sceneIO/usd/UsdConversions.h"

namespace crayg {

UsdPreviewSurfaceWriter::UsdPreviewSurfaceWriter(UsdPreviewSurface &craygObject) : BaseUsdMaterialWriter(craygObject) {
}

std::string UsdPreviewSurfaceWriter::getTranslatedType() {
    return "UsdPreviewSurface";
}

pxr::UsdShadeMaterial UsdPreviewSurfaceWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdPreviewSurfaceMaterial = BaseUsdMaterialWriter::write(stage, usdPathFactory);
    auto usdPreviewSurfaceShader = usdPreviewSurfaceMaterial.ComputeSurfaceSource();

    usdPreviewSurfaceShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPreviewSurface")));
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("diffuseColor"), pxr::SdfValueTypeNames->Color3f)
        .Set(UsdConversions::convert(craygObject.diffuseColor.value));
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("emissiveColor"), pxr::SdfValueTypeNames->Color3f)
        .Set(UsdConversions::convert(craygObject.emissiveColor.value));
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("useSpecularWorkflow"), pxr::SdfValueTypeNames->Int)
        .Set(craygObject.useSpecularWorkflow == true ? 1 : 0);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("specularColor"), pxr::SdfValueTypeNames->Color3f)
        .Set(UsdConversions::convert(craygObject.specularColor.value));
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("metallic"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.metallic.value);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("roughness"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.roughness.value);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("clearcoat"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.clearcoat.value);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("clearcoatRoughness"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.clearcoatRoughness.value);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("opacity"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.opacity.value);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("opacityThreshold"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.opacityThreshold.value);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("ior"), pxr::SdfValueTypeNames->Float).Set(craygObject.ior.value);

    return usdPreviewSurfaceMaterial;
}

} // crayg