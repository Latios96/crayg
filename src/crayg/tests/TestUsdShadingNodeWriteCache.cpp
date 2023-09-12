#include "scene/materials/ConstantShadingNodes.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/materials/UsdShadingNodeWriteCache.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <pxr/usd/usdShade/materialBindingAPI.h>

namespace crayg {

pxr::UsdShadeShader getConnectedUsdShadeShader(const pxr::UsdShadeShader &shader,
                                               const pxr::UsdShadeInput &usdShadeInput) {
    pxr::UsdShadeConnectableAPI connectedOutput;
    pxr::TfToken connectedOutputName;
    pxr::UsdShadeAttributeType type;
    shader.ConnectableAPI().GetConnectedSource(usdShadeInput, &connectedOutput, &connectedOutputName, &type);
    return pxr::UsdShadeShader(connectedOutput.GetPrim());
}

TEST_CASE("UsdShadingNodeWriteCache::createInputAndWriteCachedGraph") {

    UsdPathFactory usdPathFactory;
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);
    auto shader = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/shader"));

    SECTION("should write float input graph correctly") {
        auto floatConstant = std::make_shared<FloatConstant>(.5f);
        FloatShadingNodeInput floatShadingNodeInput = .75f;
        floatShadingNodeInput.connectTo(floatConstant);

        usdShadingNodeWriteCache.createInputAndWriteCachedGraph(shader, "myFloat", floatShadingNodeInput);

        auto myFloatUsdInput = shader.GetInput(pxr::TfToken("myFloat"));
        const auto inputValue = UsdUtils::getStaticAttributeValueAs<float>(myFloatUsdInput);
        REQUIRE(inputValue == .75f);
        auto usdFloatConstantShader = getConnectedUsdShadeShader(shader, myFloatUsdInput);
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
        auto usdIntConstantShader = getConnectedUsdShadeShader(shader, myIntUsdInput);
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
        auto usdVector2fConstantShader = getConnectedUsdShadeShader(shader, myIntUsdInput);
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
        auto usdColorConstantShader = getConnectedUsdShadeShader(shader, myColorUsdInput);
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
        auto firstInstance = getConnectedUsdShadeShader(shader, firstUsdInput);
        auto secondInstance = getConnectedUsdShadeShader(shader, secondUsdInput);
        REQUIRE(firstInstance.GetPath() == secondInstance.GetPath());
    }
}

}