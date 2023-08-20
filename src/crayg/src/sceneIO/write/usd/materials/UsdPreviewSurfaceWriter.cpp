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
        .Set(UsdConversions::convert(craygObject.diffuseColor));
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("emissiveColor"), pxr::SdfValueTypeNames->Color3f)
        .Set(UsdConversions::convert(craygObject.emissiveColor));
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("useSpecularWorkflow"), pxr::SdfValueTypeNames->Int)
        .Set(craygObject.useSpecularWorkflow == true ? 1 : 0);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("specularColor"), pxr::SdfValueTypeNames->Color3f)
        .Set(UsdConversions::convert(craygObject.specularColor));
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("metallic"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.metallic);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("roughness"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.roughness);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("clearcoat"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.clearcoat);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("clearcoatRoughness"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.clearcoatRoughness);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("opacity"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.opacity);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("opacityThreshold"), pxr::SdfValueTypeNames->Float)
        .Set(craygObject.opacityThreshold);
    usdPreviewSurfaceShader.CreateInput(pxr::TfToken("ior"), pxr::SdfValueTypeNames->Float).Set(craygObject.ior);

    return usdPreviewSurfaceMaterial;
}

} // crayg