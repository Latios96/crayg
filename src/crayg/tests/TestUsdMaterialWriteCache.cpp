#include <catch2/catch.hpp>
#include "sceneIO/write/usd/UsdMaterialWriteCache.h"
#include <pxr/usd/usd/stage.h>
#include "scene/UsdPreviewSurface.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

class UnsupportedMaterial : public Material {
 public:
    explicit UnsupportedMaterial(const std::string &name) : Material(name) {}
    Color getDiffuseColor() override {
        return {};
    }
    Color evaluate(const SurfaceInteraction &surfaceInteraction) override {
        return {};
    }
    std::string getType() override {
        return "UnsupportedMaterial";
    }
};

TEST_CASE("UsdMaterialWriteCache::getCachedUsdMaterial") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory);
    auto material = std::make_shared<UsdPreviewSurface>("myMat", Color(1, 2, 3));

    SECTION("should translate material") {
        usdMaterialWriteCache.getCachedUsdMaterial(material);

        auto matPrim = pxr::UsdShadeMaterial(stage->GetPrimAtPath(pxr::SdfPath("/myMat")));
        auto shaderPrim = pxr::UsdShadeShader(stage->GetPrimAtPath(pxr::SdfPath("/myMat/usdPreviewSurface")));
        auto id = UsdUtils::getAttributeValueAs<pxr::TfToken>(shaderPrim.GetIdAttr());
        REQUIRE(id == pxr::TfToken("UsdPreviewSurface"));
        auto diffuseColor =
            UsdUtils::getAttributeValueAs<pxr::GfVec3f>(shaderPrim.GetInput(pxr::TfToken("diffuseColor")));
        REQUIRE(diffuseColor == pxr::GfVec3f(1, 2, 3));
    }

    SECTION("should translate unsupported material to UsdPreviewSurface with no authored attributes") {
        auto unsupportedMaterial = std::make_shared<UnsupportedMaterial>("myUnsupportedMat");
        usdMaterialWriteCache.getCachedUsdMaterial(unsupportedMaterial);

        auto matPrim = pxr::UsdShadeMaterial(stage->GetPrimAtPath(pxr::SdfPath("/myUnsupportedMat")));
        auto
            shaderPrim = pxr::UsdShadeShader(stage->GetPrimAtPath(pxr::SdfPath("/myUnsupportedMat/usdPreviewSurface")));
        auto id = UsdUtils::getAttributeValueAs<pxr::TfToken>(shaderPrim.GetIdAttr());
        REQUIRE(id == pxr::TfToken("UsdPreviewSurface"));
        auto diffuseColor =
            UsdUtils::getAttributeValueAs<pxr::GfVec3f>(shaderPrim.GetInput(pxr::TfToken("diffuseColor")));
        REQUIRE(diffuseColor == pxr::GfVec3f(0, 0, 0));
    }

    SECTION("translating material twice should be cached")
    {
        auto material1 = usdMaterialWriteCache.getCachedUsdMaterial(material);
        auto material2 = usdMaterialWriteCache.getCachedUsdMaterial(material);

        REQUIRE(material1.GetPrim().GetPath() == material2.GetPrim().GetPath());
    }
}
}