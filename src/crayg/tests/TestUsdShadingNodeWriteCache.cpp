#include "scene/materials/ConstantShadingNodes.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/materials/UsdShadingNodeWriteCache.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <pxr/usd/usdShade/materialBindingAPI.h>

namespace crayg {

TEST_CASE("UsdShadingNodeWriteCache::createInputAndWriteCachedGraph") {

    UsdPathFactory usdPathFactory;
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);

    SECTION("should write float input graph correctly") {
        auto floatConstant = std::make_shared<FloatConstant>(.5f);
        FloatShadingNodeInput floatShadingNodeInput = .75f;
        floatShadingNodeInput.connectTo(floatConstant);

        auto shader = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/shader"));

        usdShadingNodeWriteCache.createInputAndWriteCachedGraph(shader, "myFloat", floatShadingNodeInput);

        auto myFloatUsdInput = shader.GetInput(pxr::TfToken("myFloat"));
        const auto inputValue = UsdUtils::getStaticAttributeValueAs<float>(myFloatUsdInput);
        REQUIRE(inputValue == .75f);

        pxr::UsdShadeConnectableAPI connectedOutput;
        pxr::TfToken connectedOutputName;
        pxr::UsdShadeAttributeType type;
        shader.ConnectableAPI().GetConnectedSource(myFloatUsdInput, &connectedOutput, &connectedOutputName, &type);
        REQUIRE(connectedOutput.GetPrim().GetPath() == pxr::SdfPath("/FloatConstant0"));
        auto usdFloatConstantShader = pxr::UsdShadeShader(stage->GetPrimAtPath(connectedOutput.GetPrim().GetPath()));
        auto id = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(usdFloatConstantShader.GetIdAttr());
        REQUIRE(id == "crayg:FloatConstant");
        auto value = UsdUtils::getStaticAttributeValueAs<float>(usdFloatConstantShader.GetInput(pxr::TfToken("value")));
        REQUIRE(value == .5f);
    }

    // int, Vec3f, Color
    // test caching once
}

}