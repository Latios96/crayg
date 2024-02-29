#include "scene/shadingnetworks/shadingnodes/ConstantShadingNodes.h"
#include "sceneIO/read/usd/shadingnetworks/caches/UsdShadingNodeReadCache.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

TEST_CASE("UsdShadingNodeReadCache::getCachedOrReadShadingNode") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdFloatConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/FloatConstant"));
    usdFloatConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:FloatConstant")));
    usdFloatConstant.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Float).Set(0.1f);

    SECTION("should read shader") {
        UsdShadingNodeReadCache usdShadingNodeReadCache;

        auto shadingNode = usdShadingNodeReadCache.getCachedOrReadShadingNode(usdFloatConstant);
        auto floatConstant = std::dynamic_pointer_cast<FloatConstant>(shadingNode);

        REQUIRE(floatConstant->value == 0.1f);
    }

    SECTION("should read shader cached") {
        UsdShadingNodeReadCache usdShadingNodeReadCache;

        auto shadingNode1 = usdShadingNodeReadCache.getCachedOrReadShadingNode(usdFloatConstant);
        auto shadingNode2 = usdShadingNodeReadCache.getCachedOrReadShadingNode(usdFloatConstant);

        REQUIRE(shadingNode1.get() == shadingNode2.get());
    }
}

TEST_CASE("UsdShadingNodeReadCache::readCachedGraph") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdShadingNodeReadCache usdShadingNodeReadCache;

    auto usdFloatConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/FloatConstant"));
    usdFloatConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:FloatConstant")));
    auto usdFloatAttr = usdFloatConstant.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Float).Set(0.1f);
    auto usdFloatOutput = usdFloatConstant.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Float);

    auto usdIntConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/IntConstant"));
    usdIntConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:IntConstant")));
    auto usdIntAttr = usdIntConstant.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Int).Set(1);
    auto usdIntOutput = usdIntConstant.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Int);

    auto usdVector2fConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/Vector2fConstant"));
    usdVector2fConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:Vector2fConstant")));
    auto usdVector2fAttr =
        usdVector2fConstant.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Float2).Set(pxr::GfVec2f(1, 2));
    auto usdVector2fOutput = usdVector2fConstant.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Float2);

    auto usdColorConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/ColorConstant"));
    usdColorConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:ColorConstant")));
    auto usdColorAttr = usdColorConstant.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Vector3f)
                            .Set(pxr::GfVec3f(1, 2, 3));
    auto usdColorOutput = usdColorConstant.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Vector3f);

    auto usdMaterialShader = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/Material"));
    auto usdFloatInput = usdMaterialShader.CreateInput(pxr::TfToken("floatInput"), pxr::SdfValueTypeNames->Float);
    usdFloatInput.Set(0.2f);
    auto usdIntInput = usdMaterialShader.CreateInput(pxr::TfToken("intInput"), pxr::SdfValueTypeNames->Int);
    usdIntInput.Set(1);
    auto usdVector2fInput =
        usdMaterialShader.CreateInput(pxr::TfToken("vector2fInput"), pxr::SdfValueTypeNames->Float2);
    usdVector2fInput.Set(pxr::GfVec2f(4, 5));
    auto usdColorInput = usdMaterialShader.CreateInput(pxr::TfToken("ColorInput"), pxr::SdfValueTypeNames->Vector3f);
    usdColorInput.Set(pxr::GfVec3f(4, 5, 6));

    SECTION("should read connected float constant with no value authored") {
        auto floatConstantNoValueAuthored = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/FloatConstant"));
        floatConstantNoValueAuthored.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:FloatConstant")));
        auto floatConstantNoValueAuthoredOutput =
            floatConstantNoValueAuthored.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Float);
        usdFloatInput.ConnectToSource(floatConstantNoValueAuthoredOutput);
        FloatShadingNodeInput targetInput;

        usdShadingNodeReadCache.readCachedGraph(usdMaterialShader, usdFloatInput, targetInput);

        REQUIRE(targetInput.value == 0.2f);
        REQUIRE(targetInput.hasInputConnection());
    }

    SECTION("should read float graph without connections") {
        FloatShadingNodeInput targetInput;

        usdShadingNodeReadCache.readCachedGraph(usdMaterialShader, usdFloatInput, targetInput);

        REQUIRE(targetInput.value == 0.2f);
        REQUIRE_FALSE(targetInput.hasInputConnection());
    }

    SECTION("should read float graph with connections") {
        usdFloatInput.ConnectToSource(usdFloatOutput);
        FloatShadingNodeInput targetInput;

        usdShadingNodeReadCache.readCachedGraph(usdMaterialShader, usdFloatInput, targetInput);

        REQUIRE(targetInput.value == 0.2f);
        REQUIRE(targetInput.hasInputConnection());
        REQUIRE(targetInput.inputNode->getType() == "FloatConstant");
    }

    SECTION("should read int graph without connections") {
        IntShadingNodeInput targetInput;

        usdShadingNodeReadCache.readCachedGraph(usdMaterialShader, usdIntInput, targetInput);

        REQUIRE(targetInput.value == 1);
        REQUIRE_FALSE(targetInput.hasInputConnection());
    }

    SECTION("should read int graph with connections") {
        usdIntInput.ConnectToSource(usdIntOutput);
        IntShadingNodeInput targetInput;

        usdShadingNodeReadCache.readCachedGraph(usdMaterialShader, usdIntInput, targetInput);

        REQUIRE(targetInput.value == 1);
        REQUIRE(targetInput.hasInputConnection());
        REQUIRE(targetInput.inputNode->getType() == "IntConstant");
    }

    SECTION("should read Vector2f graph without connections") {
        Vector2fShadingNodeInput targetInput;

        usdShadingNodeReadCache.readCachedGraph(usdMaterialShader, usdVector2fInput, targetInput);

        REQUIRE(targetInput.value == Vector2f(4, 5));
        REQUIRE_FALSE(targetInput.hasInputConnection());
    }

    SECTION("should read Vector2f graph with connections") {
        usdVector2fInput.ConnectToSource(usdVector2fOutput);
        Vector2fShadingNodeInput targetInput;

        usdShadingNodeReadCache.readCachedGraph(usdMaterialShader, usdVector2fInput, targetInput);

        REQUIRE(targetInput.value == Vector2f(4, 5));
        REQUIRE(targetInput.hasInputConnection());
        REQUIRE(targetInput.inputNode->getType() == "Vector2fConstant");
    }

    SECTION("should read Color graph without connections") {
        ColorShadingNodeInput targetInput;

        usdShadingNodeReadCache.readCachedGraph(usdMaterialShader, usdColorInput, targetInput);

        REQUIRE(targetInput.value == Color(4, 5, 6));
        REQUIRE_FALSE(targetInput.hasInputConnection());
    }

    SECTION("should read Color graph with connections") {
        usdColorInput.ConnectToSource(usdColorOutput);
        ColorShadingNodeInput targetInput;

        usdShadingNodeReadCache.readCachedGraph(usdMaterialShader, usdColorInput, targetInput);

        REQUIRE(targetInput.value == Color(4, 5, 6));
        REQUIRE(targetInput.hasInputConnection());
        REQUIRE(targetInput.inputNode->getType() == "ColorConstant");
    }
}

}