#include "sceneIO/read/usd/shadingnetworks/caches/UsdShadingNodeReadCache.h"
#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdCheckerBoardReader.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

TEST_CASE("TestUsdCheckerBoardReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdFloatConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/CheckerBoard"));
    usdFloatConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:CheckerBoard")));
    usdFloatConstant.CreateInput(pxr::TfToken("colorA"), pxr::SdfValueTypeNames->Color3f).Set(pxr::GfVec3f(1, 0, 0));
    usdFloatConstant.CreateInput(pxr::TfToken("colorB"), pxr::SdfValueTypeNames->Color3f).Set(pxr::GfVec3f(0, 1, 0));
    usdFloatConstant.CreateInput(pxr::TfToken("uvInput"), pxr::SdfValueTypeNames->TexCoord2d).Set(pxr::GfVec2f(0));
    usdFloatConstant.CreateInput(pxr::TfToken("repetitions"), pxr::SdfValueTypeNames->Int).Set(2);
    UsdShadingNodeReadCache usdShadingNodeReadCache;

    SECTION("should read correctly") {
        UsdCheckerBoardReader usdCheckerBoardReader(usdFloatConstant, usdShadingNodeReadCache);

        auto checkerBoard = usdCheckerBoardReader.read();

        REQUIRE(checkerBoard->repetitions == 2);
        REQUIRE(checkerBoard->colorA == Color::createRed());
        REQUIRE(checkerBoard->colorB == Color::createGreen());
    }
}
}