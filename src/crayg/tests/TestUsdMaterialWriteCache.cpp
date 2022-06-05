#include <catch2/catch.hpp>
#include "sceneIO/write/usd/UsdMaterialWriteCache.h"
#include <pxr/usd/usd/stage.h>
#include "scene/DiffuseMaterial.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

TEST_CASE("UsdMaterialWriteCache::getCachedUsdMaterial") {

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory);
    auto material = std::make_shared<DiffuseMaterial>("myMat", Color(1, 2, 3));

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

    SECTION("translating material twice should be cached")
    {
        auto material1 = usdMaterialWriteCache.getCachedUsdMaterial(material);
        auto material2 = usdMaterialWriteCache.getCachedUsdMaterial(material);

        REQUIRE(material1.GetPrim().GetPath() == material2.GetPrim().GetPath());
    }
}
}