#include "crayg/scene/io/usd/UsdUtils.h"
#include "crayg/scene/io/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"
#include "crayg/scene/shadingnetworks/shadingnodes/ConstantShadingNodes.h"
#include "crayg/scene/shadingnetworks/shadingnodes/ConversionNodes.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <pxr/usd/usdShade/materialBindingAPI.h>

namespace crayg {

TEST_CASE("UsdShadingNodeWriteCache::createInputAndWriteCachedGraph") {

    UsdPathFactory usdPathFactory;
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);
    auto shader = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/shader"));
    pxr::TfToken connectedOutputName;

    SECTION("should write float input graph correctly") {
        auto floatConstant = std::make_shared<FloatConstant>(.5f);
        FloatShadingNodeInput floatShadingNodeInput = .75f;
        floatShadingNodeInput.connectTo(floatConstant);

        usdShadingNodeWriteCache.createInputAndWriteCachedGraph(shader, "myFloat", floatShadingNodeInput);

        auto myFloatUsdInput = shader.GetInput(pxr::TfToken("myFloat"));
        const auto inputValue = UsdUtils::getStaticAttributeValueAs<float>(myFloatUsdInput);
        REQUIRE(inputValue == .75f);
        auto usdFloatConstantShader =
            UsdUtils::getConnectedUsdShadeShader(shader, myFloatUsdInput, connectedOutputName);
        REQUIRE(usdFloatConstantShader.GetPath() == pxr::SdfPath("/FloatConstant0"));
        auto id = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(usdFloatConstantShader.GetIdAttr());
        REQUIRE(id == "crayg:FloatConstant");
        auto value = UsdUtils::getStaticAttributeValueAs<float>(usdFloatConstantShader.GetInput(pxr::TfToken("value")));
        REQUIRE(value == .5f);
    }

    SECTION("should write int input graph correctly") {
        auto intConstant = std::make_shared<IntConstant>(5);
        IntShadingNodeInput intShadingNodeInput = 7;
        intShadingNodeInput.connectTo(intConstant);

        usdShadingNodeWriteCache.createInputAndWriteCachedGraph(shader, "myInt", intShadingNodeInput);

        auto myIntUsdInput = shader.GetInput(pxr::TfToken("myInt"));
        const auto inputValue = UsdUtils::getStaticAttributeValueAs<int>(myIntUsdInput);
        REQUIRE(inputValue == 7);
        auto usdIntConstantShader = UsdUtils::getConnectedUsdShadeShader(shader, myIntUsdInput, connectedOutputName);
        REQUIRE(usdIntConstantShader.GetPath() == pxr::SdfPath("/IntConstant0"));
        auto id = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(usdIntConstantShader.GetIdAttr());
        REQUIRE(id == "crayg:IntConstant");
        auto value = UsdUtils::getStaticAttributeValueAs<int>(usdIntConstantShader.GetInput(pxr::TfToken("value")));
        REQUIRE(value == 5);
    }

    SECTION("should write Vector2f input graph correctly") {
        auto vector2fConstant = std::make_shared<Vector2fConstant>(Vector2f(5));
        Vector2fShadingNodeInput vector2fShadingNodeInput = Vector2f(7);
        vector2fShadingNodeInput.connectTo(vector2fConstant);

        usdShadingNodeWriteCache.createInputAndWriteCachedGraph(shader, "myVector2f", vector2fShadingNodeInput);

        auto myIntUsdInput = shader.GetInput(pxr::TfToken("myVector2f"));
        const auto inputValue = UsdUtils::getStaticAttributeValueAs<pxr::GfVec2f>(myIntUsdInput);
        REQUIRE(inputValue == pxr::GfVec2f(7));
        auto usdVector2fConstantShader =
            UsdUtils::getConnectedUsdShadeShader(shader, myIntUsdInput, connectedOutputName);
        REQUIRE(usdVector2fConstantShader.GetPath() == pxr::SdfPath("/Vector2fConstant0"));
        auto id = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(usdVector2fConstantShader.GetIdAttr());
        REQUIRE(id == "crayg:Vector2fConstant");
        auto value = UsdUtils::getStaticAttributeValueAs<pxr::GfVec2f>(
            usdVector2fConstantShader.GetInput(pxr::TfToken("value")));
        REQUIRE(value == pxr::GfVec2f(5));
    }

    SECTION("should write Color input graph correctly") {
        auto colorConstant = std::make_shared<ColorConstant>(Color::createGrey(.5f));
        ColorShadingNodeInput colorShadingNodeInput = Color::createGrey(.7f);
        colorShadingNodeInput.connectTo(colorConstant);

        usdShadingNodeWriteCache.createInputAndWriteCachedGraph(shader, "myColor", colorShadingNodeInput);

        auto myColorUsdInput = shader.GetInput(pxr::TfToken("myColor"));
        const auto inputValue = UsdUtils::getStaticAttributeValueAs<pxr::GfVec3f>(myColorUsdInput);
        REQUIRE(inputValue == pxr::GfVec3f(.7f));
        auto usdColorConstantShader =
            UsdUtils::getConnectedUsdShadeShader(shader, myColorUsdInput, connectedOutputName);
        REQUIRE(usdColorConstantShader.GetPath() == pxr::SdfPath("/ColorConstant0"));
        auto id = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(usdColorConstantShader.GetIdAttr());
        REQUIRE(id == "crayg:ColorConstant");
        auto value =
            UsdUtils::getStaticAttributeValueAs<pxr::GfVec3f>(usdColorConstantShader.GetInput(pxr::TfToken("value")));
        REQUIRE(value == pxr::GfVec3f(.5f));
    }

    SECTION("should cache writing of input graphs") {
        auto floatConstant = std::make_shared<FloatConstant>(.5f);
        FloatShadingNodeInput firstInput = .1;
        firstInput.connectTo(floatConstant);
        FloatShadingNodeInput secondInput = .2;
        secondInput.connectTo(floatConstant);

        usdShadingNodeWriteCache.createInputAndWriteCachedGraph(shader, "firstInput", firstInput);
        usdShadingNodeWriteCache.createInputAndWriteCachedGraph(shader, "secondInput", secondInput);

        auto firstUsdInput = shader.GetInput(pxr::TfToken("firstInput"));
        auto secondUsdInput = shader.GetInput(pxr::TfToken("secondInput"));
        auto firstInstance = UsdUtils::getConnectedUsdShadeShader(shader, firstUsdInput, connectedOutputName);
        auto secondInstance = UsdUtils::getConnectedUsdShadeShader(shader, secondUsdInput, connectedOutputName);
        REQUIRE(firstInstance.GetPath() == secondInstance.GetPath());
    }

    SECTION("should support recursive writes") {
        auto vector2fConstant = std::make_shared<Vector2fConstant>(Vector2f(1, 2));
        auto vector2fToColor = std::make_shared<Vector2fToColor>();
        vector2fToColor->vector2fInput.connectTo(vector2fConstant);
        ColorShadingNodeInput colorShadingNodeInput;
        colorShadingNodeInput.connectTo(vector2fToColor);

        usdShadingNodeWriteCache.createInputAndWriteCachedGraph(shader, "myColor", colorShadingNodeInput);

        auto usdMyColor = shader.GetInput(pxr::TfToken("myColor"));
        auto usdVector2fToColor = UsdUtils::getConnectedUsdShadeShader(shader, usdMyColor, connectedOutputName);
        auto usdVector2fInput = usdVector2fToColor.GetInput(pxr::TfToken("vector2fInput"));
        auto usdVector2fConstant = UsdUtils::getConnectedUsdShadeShader(shader, usdVector2fInput, connectedOutputName);
    }
}

}