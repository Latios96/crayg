#include "scene/shadingnetworks/shadingnodes/ColorToFloat.h"
#include "scene/shadingnetworks/shadingnodes/ConstantShadingNodes.h"
#include "sceneIO/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include "sceneIO/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"
#include "sceneIO/write/usd/shadingnetworks/shadingnodes/UsdColorToFloatWriter.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>

namespace crayg {

TEST_CASE("TestUsdColorToFloatWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);

    SECTION("should write correctly") {
        auto constantColor = std::make_shared<ColorConstant>();
        ColorToFloat colorToFloat;
        colorToFloat.colorToFloatMode = ColorToFloatMode::G;
        colorToFloat.colorInput.connectTo(constantColor);

        UsdColorToFloatWriter usdColorToFloatWriter(colorToFloat, usdShadingNodeWriteCache);

        auto shaderAndOutput = usdColorToFloatWriter.writeAndGetShaderAndOutput(stage, usdPathFactory);

        REQUIRE(shaderAndOutput.shader.GetPath() == pxr::SdfPath("/ColorToFloat0"));
        REQUIRE(shaderAndOutput.output.GetFullName() == pxr::TfToken("outputs:out"));

        const auto colorToFloatMode = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            shaderAndOutput.shader.GetPrim().GetAttribute(pxr::TfToken("colorToFloatMode")));
        REQUIRE(colorToFloatMode == pxr::TfToken("G"));
    }
}

}