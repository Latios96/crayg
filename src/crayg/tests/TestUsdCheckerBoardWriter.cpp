#include "scene/io/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h"
#include "scene/io/usd/UsdUtils.h"
#include "scene/io/write/usd/UsdPathFactory.h"
#include "scene/io/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"
#include "scene/io/write/usd/shadingnetworks/shadingnodes/UsdCheckerBoardWriter.h"
#include "scene/io/write/usd/shadingnetworks/shadingnodes/UsdConstantShadingNodeWriters.h"
#include "scene/shadingnetworks/shadingnodes/CheckerBoard.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>

namespace crayg {

TEST_CASE("TestUsdCheckerBoardWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);

    SECTION("should write correctly") {
        CheckerBoard checkerBoard;
        checkerBoard.colorA.value = Color(1, 0, 0);
        checkerBoard.colorB.value = Color(0, 1, 0);
        UsdCheckerBoardWriter usdCheckerBoardWriter(checkerBoard, usdShadingNodeWriteCache);

        auto shaderAndOutput = usdCheckerBoardWriter.writeAndGetShaderAndOutput(stage, usdPathFactory);

        REQUIRE(shaderAndOutput.shader.GetPath() == pxr::SdfPath("/CheckerBoard0"));
        REQUIRE(shaderAndOutput.output.GetFullName() == pxr::TfToken("outputs:out"));

        auto repetitions =
            UsdUtils::getStaticAttributeValueAs<int>(shaderAndOutput.shader.GetInput(pxr::TfToken("repetitions")));
        REQUIRE(repetitions == 4);

        Color colorA, colorB;
        UsdShadingNodeReadUtils::readShaderAttributeValue<Color, pxr::GfVec3f>(shaderAndOutput.shader, "colorA",
                                                                               colorA);
        UsdShadingNodeReadUtils::readShaderAttributeValue<Color, pxr::GfVec3f>(shaderAndOutput.shader, "colorB",
                                                                               colorB);

        REQUIRE(colorA == Color(1, 0, 0));
        REQUIRE(colorB == Color(0, 1, 0));
    }
}

}