#include "scene/shadingnetworks/shadingnodes/ConstantShadingNodes.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"
#include "sceneIO/write/usd/shadingnetworks/shadingnodes/UsdConstantShadingNodeWriters.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("TestUsdFloatConstantWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);

    SECTION("should write correctly") {
        FloatConstant floatConstant = .5f;
        UsdFloatConstantWriter usdFloatConstantWriter(floatConstant, usdShadingNodeWriteCache);

        auto shaderAndOutput = usdFloatConstantWriter.writeAndGetShaderAndOutput(stage, usdPathFactory);

        REQUIRE(shaderAndOutput.shader.GetPath() == pxr::SdfPath("/FloatConstant0"));
        REQUIRE(shaderAndOutput.output.GetFullName() == pxr::TfToken("outputs:out"));

        auto value = UsdUtils::getStaticAttributeValueAs<float>(shaderAndOutput.shader.GetInput(pxr::TfToken("value")));
        REQUIRE(value == .5f);
    }
}

TEST_CASE("TestUsdIntConstantWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);

    SECTION("should write correctly") {
        IntConstant intConstant = 5;
        UsdIntConstantWriter usdIntConstantWriter(intConstant, usdShadingNodeWriteCache);

        auto shaderAndOutput = usdIntConstantWriter.writeAndGetShaderAndOutput(stage, usdPathFactory);

        REQUIRE(shaderAndOutput.shader.GetPath() == pxr::SdfPath("/IntConstant0"));
        REQUIRE(shaderAndOutput.output.GetFullName() == pxr::TfToken("outputs:out"));

        auto value = UsdUtils::getStaticAttributeValueAs<int>(shaderAndOutput.shader.GetInput(pxr::TfToken("value")));
        REQUIRE(value == 5);
    }
}

TEST_CASE("TestUsdVector2fConstantWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);

    SECTION("should write correctly") {
        Vector2fConstant vector2fConstant = Vector2f(.5f);
        UsdVector2fConstantWriter usdVector2fConstantWriter(vector2fConstant, usdShadingNodeWriteCache);

        auto shaderAndOutput = usdVector2fConstantWriter.writeAndGetShaderAndOutput(stage, usdPathFactory);

        REQUIRE(shaderAndOutput.shader.GetPath() == pxr::SdfPath("/Vector2fConstant0"));
        REQUIRE(shaderAndOutput.output.GetFullName() == pxr::TfToken("outputs:out"));

        auto value =
            UsdUtils::getStaticAttributeValueAs<pxr::GfVec2f>(shaderAndOutput.shader.GetInput(pxr::TfToken("value")));
        REQUIRE(value == pxr::GfVec2f(.5f));
    }
}

TEST_CASE("TestUsdColorConstantWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);

    SECTION("should write correctly") {
        ColorConstant colorConstant = Color::createGrey(.5f);
        UsdColorConstantWriter usdColorConstantWriter(colorConstant, usdShadingNodeWriteCache);

        auto shaderAndOutput = usdColorConstantWriter.writeAndGetShaderAndOutput(stage, usdPathFactory);

        REQUIRE(shaderAndOutput.shader.GetPath() == pxr::SdfPath("/ColorConstant0"));
        REQUIRE(shaderAndOutput.output.GetFullName() == pxr::TfToken("outputs:out"));

        auto value =
            UsdUtils::getStaticAttributeValueAs<pxr::GfVec3f>(shaderAndOutput.shader.GetInput(pxr::TfToken("value")));
        REQUIRE(value == pxr::GfVec3f(.5f));
    }
}

}