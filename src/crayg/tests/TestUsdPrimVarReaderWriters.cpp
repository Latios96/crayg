#include "scene/shadingnetworks/shadingnodes/PrimVarReaders.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include "sceneIO/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"
#include "sceneIO/write/usd/shadingnetworks/shadingnodes/UsdPrimVarReaderWriters.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>

namespace crayg {

TEST_CASE("TestUsdPrimVarReaderVector2fWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);

    SECTION("should write correctly") {
        PrimVarReaderVector2f primVarReaderVector2f;
        primVarReaderVector2f.primVarReaderType = PrimVarReaderType::UV;
        UsdPrimVarReaderVector2fWriter usdPrimVarReaderVector2fWriter(primVarReaderVector2f, usdShadingNodeWriteCache);

        auto shaderAndOutput = usdPrimVarReaderVector2fWriter.writeAndGetShaderAndOutput(stage, usdPathFactory);

        REQUIRE(shaderAndOutput.shader.GetPath() == pxr::SdfPath("/PrimVarReaderVector2f0"));
        REQUIRE(shaderAndOutput.output.GetFullName() == pxr::TfToken("outputs:out"));

        const auto type = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            shaderAndOutput.shader.GetPrim().GetAttribute(pxr::TfToken("primVarReaderType")));
        REQUIRE(type == pxr::TfToken("UV"));
    }
}

}