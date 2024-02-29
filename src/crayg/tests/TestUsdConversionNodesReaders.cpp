#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdConversionNodesReaders.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

TEST_CASE("TestUsdVector2fToColorReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdFloatConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/Vector2fToColor"));
    usdFloatConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:Vector2fToColor")));

    SECTION("should read correctly") {
        UsdVector2fToColorReader vector2fToColorReader(usdFloatConstant);

        auto vector2FToColor = vector2fToColorReader.read();

        REQUIRE(vector2FToColor->getType() == "Vector2fToColor");
    }
}

}