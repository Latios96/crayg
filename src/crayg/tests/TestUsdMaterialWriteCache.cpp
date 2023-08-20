#include "scene/materials/UsdPreviewSurface.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/UsdMaterialWriteCache.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>

namespace crayg {

class UnsupportedMaterial : public Material {
  public:
    explicit UnsupportedMaterial(const std::string &name) : Material(name) {
    }

    Color evaluate(const SurfaceInteraction &surfaceInteraction, IntegratorContext &integratorContext) override {
        return {};
    }

    std::string getType() override {
        return "UnsupportedMaterial";
    }

    ShadingNodeOutputType getOutputType() override {
        return COLOR;
    }
};

TEST_CASE("UsdMaterialWriteCache::getCachedUsdMaterial") {

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

    SECTION("should translate material") {
        usdMaterialWriteCache.getCachedUsdMaterial(material);

        auto matPrim = pxr::UsdShadeMaterial(stage->GetPrimAtPath(pxr::SdfPath("/myMat")));
        auto shaderPrim = pxr::UsdShadeShader(stage->GetPrimAtPath(pxr::SdfPath("/myMat/usdPreviewSurface")));
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

    SECTION("should translate unsupported material to UsdPreviewSurface with no authored attributes") {
        auto unsupportedMaterial = std::make_shared<UnsupportedMaterial>("myUnsupportedMat");
        usdMaterialWriteCache.getCachedUsdMaterial(unsupportedMaterial);

        auto matPrim = pxr::UsdShadeMaterial(stage->GetPrimAtPath(pxr::SdfPath("/myUnsupportedMat")));
        auto shaderPrim =
            pxr::UsdShadeShader(stage->GetPrimAtPath(pxr::SdfPath("/myUnsupportedMat/usdPreviewSurface")));
        auto id = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(shaderPrim.GetIdAttr());
        REQUIRE(id == pxr::TfToken("UsdPreviewSurface"));
        auto diffuseColorAttr = shaderPrim.GetInput(pxr::TfToken("diffuseColor"));
        REQUIRE_FALSE(diffuseColorAttr);
    }

    SECTION("translating material twice should be cached") {
        auto material1 = usdMaterialWriteCache.getCachedUsdMaterial(material);
        auto material2 = usdMaterialWriteCache.getCachedUsdMaterial(material);

        REQUIRE(material1.GetPrim().GetPath() == material2.GetPrim().GetPath());
    }
}
}