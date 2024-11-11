#include "sceneIO/read/usd/shadingnetworks/caches/UsdShadingNodeReadCache.h"
#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdColorToFloatReader.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

TEST_CASE("TestUsdColorToFloatReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdShadingNodeReadCache usdShadingNodeReadCache;

    SECTION("should read correctly") {
        auto usdPrim = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/UsdColorToFloat"));
        usdPrim.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:ColorToFloat")));
        usdPrim.GetPrim()
            .CreateAttribute(pxr::TfToken("colorToFloatMode"), pxr::SdfValueTypeNames->Token)
            .Set(pxr::TfToken("G"));
        UsdColorToFloatReader usdColorToFloatReader(usdPrim, usdShadingNodeReadCache);

        auto colorToFloat = usdColorToFloatReader.read();

        REQUIRE(colorToFloat->colorToFloatMode == ColorToFloatMode::G);
    }
}

}