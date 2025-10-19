#include "scene/io/read/usd/shadingnetworks/caches/UsdShadingNodeReadCache.h"
#include "scene/io/read/usd/shadingnetworks/shadingnodes/UsdFileTextureReader.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

TEST_CASE("TestUsdFileTextureReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdShadingNodeReadCache usdShadingNodeReadCache;

    SECTION("should read UsdUVTexture correctly") {
        auto usdUvTexture = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/UsdUVTexture"));
        usdUvTexture.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdUVTexture")));
        usdUvTexture.CreateInput(pxr::TfToken("file"), pxr::SdfValueTypeNames->Asset)
            .Set(pxr::SdfAssetPath("./some-file-path.png"));
        usdUvTexture.CreateInput(pxr::TfToken("fallback"), pxr::SdfValueTypeNames->Color4f)
            .Set(pxr::GfVec4f(1, 2, 3, 4));
        usdUvTexture.CreateInput(pxr::TfToken("st"), pxr::SdfValueTypeNames->TexCoord2f).Set(pxr::GfVec2f(1));

        UsdFileTextureReader usdFileTextureReader(usdUvTexture, usdShadingNodeReadCache);

        auto fileTexture = usdFileTextureReader.read();

        REQUIRE(fileTexture->getFilePath() == "./some-file-path.png");
        REQUIRE(fileTexture->fallbackColor == Color(1, 2, 3));
        REQUIRE(fileTexture->uvInput.value == Vector2f(1));
    }

    SECTION("should read crayg:FileTexture correctly") {
        auto usdUvTexture = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/fileTexture"));
        usdUvTexture.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:FileTexture")));
        usdUvTexture.CreateInput(pxr::TfToken("file"), pxr::SdfValueTypeNames->Asset)
            .Set(pxr::SdfAssetPath("./some-file-path.png"));
        usdUvTexture.CreateInput(pxr::TfToken("fallbackColor"), pxr::SdfValueTypeNames->Color4f)
            .Set(pxr::GfVec4f(1, 2, 3, 4));
        usdUvTexture.CreateInput(pxr::TfToken("uvInput"), pxr::SdfValueTypeNames->TexCoord2f).Set(pxr::GfVec2f(1));

        UsdFileTextureReader usdFileTextureReader(usdUvTexture, usdShadingNodeReadCache);

        auto fileTexture = usdFileTextureReader.read();

        REQUIRE(fileTexture->getFilePath() == "./some-file-path.png");
        REQUIRE(fileTexture->fallbackColor == Color(1, 2, 3));
        REQUIRE(fileTexture->uvInput.value == Vector2f(1));
    }
}

}