#include "crayg/scene/io/read/usd/shadingnetworks/shadingnodes/UsdConversionNodesReaders.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

TEST_CASE("TestUsdVector2fToColorReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdVector2fConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/Vector2fConstant"));
    usdVector2fConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:Vector2fConstant")));
    auto out = usdVector2fConstant.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Float2);
    auto usdVector2fToColor = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/Vector2fToColor"));
    usdVector2fToColor.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:Vector2fToColor")));
    auto input = usdVector2fToColor.CreateInput(pxr::TfToken("vector2fInput"), pxr::SdfValueTypeNames->Float2);
    input.ConnectToSource(out);
    UsdShadingNodeReadCache usdShadingNodeReadCache;

    SECTION("should read correctly") {
        UsdVector2fToColorReader vector2fToColorReader(usdVector2fToColor, usdShadingNodeReadCache);

        auto shadingNode = vector2fToColorReader.read();

        REQUIRE(shadingNode->getType() == "Vector2fToColor");
        auto vector2fToColor = std::dynamic_pointer_cast<Vector2fToColor>(shadingNode);
        REQUIRE(vector2fToColor->vector2fInput.hasInputConnection());
    }
}

}