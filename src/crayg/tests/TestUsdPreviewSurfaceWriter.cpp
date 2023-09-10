#include "scene/materials/UsdPreviewSurface.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/materials/UsdMaterialWriteCache.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>

namespace crayg {

TEST_CASE("UsdPreviewSurfaceWriter::write") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory);
    auto material = std::make_shared<UsdPreviewSurface>("myMat");
    material->diffuseColor = Color(1, 2, 3);
    material->emissiveColor = Color(4, 5, 6);
    material->useSpecularWorkflow = true;
    material->specularColor = Color(7, 8, 9);
    material->metallic = 0.1f;
    material->roughness = 0.2f;
    material->clearcoat = 0.3f;
    material->clearcoatRoughness = 0.4f;
    material->opacity = 0.5f;
    material->opacityThreshold = 0.6f;
    material->ior = 0.7f;

    SECTION("should translate material correctly") {
        usdMaterialWriteCache.getCachedUsdMaterial(material);

        auto matPrim = pxr::UsdShadeMaterial(stage->GetPrimAtPath(pxr::SdfPath("/myMat")));

        auto d = matPrim.ComputeSurfaceSource().GetPath().GetString();
        auto shaderPrim = pxr::UsdShadeShader(stage->GetPrimAtPath(pxr::SdfPath("/myMat/UsdPreviewSurface")));
        auto id = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(shaderPrim.GetIdAttr());
        REQUIRE(id == pxr::TfToken("UsdPreviewSurface"));
        auto diffuseColor =
            UsdUtils::getStaticAttributeValueAs<pxr::GfVec3f>(shaderPrim.GetInput(pxr::TfToken("diffuseColor")));
        REQUIRE(diffuseColor == pxr::GfVec3f(1, 2, 3));
        auto emissiveColor =
            UsdUtils::getStaticAttributeValueAs<pxr::GfVec3f>(shaderPrim.GetInput(pxr::TfToken("emissiveColor")));
        REQUIRE(emissiveColor == pxr::GfVec3f(4, 5, 6));
        auto useSpecularWorkflow =
            UsdUtils::getStaticAttributeValueAs<int>(shaderPrim.GetInput(pxr::TfToken("useSpecularWorkflow")));
        REQUIRE(useSpecularWorkflow == 1);
        auto specularColor =
            UsdUtils::getStaticAttributeValueAs<pxr::GfVec3f>(shaderPrim.GetInput(pxr::TfToken("specularColor")));
        REQUIRE(specularColor == pxr::GfVec3f(7, 8, 9));
        auto metallic = UsdUtils::getStaticAttributeValueAs<float>(shaderPrim.GetInput(pxr::TfToken("metallic")));
        REQUIRE(metallic == 0.1f);
        auto roughness = UsdUtils::getStaticAttributeValueAs<float>(shaderPrim.GetInput(pxr::TfToken("roughness")));
        REQUIRE(roughness == 0.2f);
        auto clearcoat = UsdUtils::getStaticAttributeValueAs<float>(shaderPrim.GetInput(pxr::TfToken("clearcoat")));
        REQUIRE(clearcoat == 0.3f);
        auto clearcoatRoughness =
            UsdUtils::getStaticAttributeValueAs<float>(shaderPrim.GetInput(pxr::TfToken("clearcoatRoughness")));
        REQUIRE(clearcoatRoughness == 0.4f);
        auto opacity = UsdUtils::getStaticAttributeValueAs<float>(shaderPrim.GetInput(pxr::TfToken("opacity")));
        REQUIRE(opacity == 0.5f);
        auto opacityThreshold =
            UsdUtils::getStaticAttributeValueAs<float>(shaderPrim.GetInput(pxr::TfToken("opacityThreshold")));
        REQUIRE(opacityThreshold == 0.6f);
        auto ior = UsdUtils::getStaticAttributeValueAs<float>(shaderPrim.GetInput(pxr::TfToken("ior")));
        REQUIRE(ior == 0.7f);
    }
}

}