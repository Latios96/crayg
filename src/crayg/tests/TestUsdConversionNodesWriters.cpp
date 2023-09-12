#include "scene/materials/ConstantShadingNodes.h"
#include "scene/materials/ConversionNodes.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/materials/UsdConversionNodeWriters.h"
#include "sceneIO/write/usd/materials/UsdShadingNodeWriteCache.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("UsdVector2fToColorWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);

    SECTION("should write correctly") {
        auto vector2fConstant = std::make_shared<Vector2fConstant>(Vector2f(.5f));
        Vector2fToColor vector2fToColor;
        vector2fToColor.vector2fInput.connectTo(vector2fConstant);

        UsdVector2fToColorWriter usdVector2fToColorWriter(vector2fToColor, usdShadingNodeWriteCache);

        auto shaderAndOutput = usdVector2fToColorWriter.writeAndGetShaderAndOutput(stage, usdPathFactory);

        REQUIRE(shaderAndOutput.shader.GetPath() == pxr::SdfPath("/Vector2fToColor0"));
        REQUIRE(shaderAndOutput.output.GetFullName() == pxr::TfToken("outputs:out"));
        auto usdVector2fInput = shaderAndOutput.shader.GetInput(pxr::TfToken("vector2fInput"));
        auto usdVector2fConstant = UsdUtils::getConnectedUsdShadeShader(shaderAndOutput.shader, usdVector2fInput);
        REQUIRE(usdVector2fConstant.GetPath() == pxr::SdfPath("/Vector2fConstant0"));
    }
}

}