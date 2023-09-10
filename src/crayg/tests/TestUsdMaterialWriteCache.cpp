#include "scene/materials/UsdPreviewSurface.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/materials/UsdMaterialWriteCache.h"
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

        REQUIRE(matPrim);
    }

    SECTION("should translate unsupported material to UsdPreviewSurface with no authored attributes") {
        auto unsupportedMaterial = std::make_shared<UnsupportedMaterial>("myUnsupportedMat");
        usdMaterialWriteCache.getCachedUsdMaterial(unsupportedMaterial);

        auto matPrim = pxr::UsdShadeMaterial(stage->GetPrimAtPath(pxr::SdfPath("/myUnsupportedMat")));
        auto shaderPrim =
            pxr::UsdShadeShader(stage->GetPrimAtPath(pxr::SdfPath("/myUnsupportedMat/UsdPreviewSurface")));
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