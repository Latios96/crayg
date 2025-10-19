#include "scene/io/read/usd/shadingnetworks/shadingnodes/UsdPrimVarReaderReaders.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

TEST_CASE("UsdPrimVarReaderVector2fReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdShadingNodeReadCache usdShadingNodeReadCache;

    SECTION("should read PrimVarReaderVector2f correctly") {
        auto usdPrimVarReaderVector2f = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/PrimVarReaderVector2f"));
        usdPrimVarReaderVector2f.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:PrimVarReaderVector2f")));
        usdPrimVarReaderVector2f.GetPrim()
            .CreateAttribute(pxr::TfToken("primVarReaderType"), pxr::SdfValueTypeNames->Token)
            .Set(pxr::TfToken("UV"));
        UsdPrimVarReaderVector2fReader readerVector2fReader(usdPrimVarReaderVector2f, usdShadingNodeReadCache);

        auto primVarReaderVector2f = readerVector2fReader.read();

        REQUIRE(primVarReaderVector2f->primVarReaderType == PrimVarReaderType::UV);
    }

    SECTION("should read UsdPrimvarReader_float2 correctly") {
        auto varnameHolder = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/varnameHolder"));
        auto varnameHolderInput = varnameHolder.CreateInput(pxr::TfToken("varname"), pxr::SdfValueTypeNames->String);
        varnameHolderInput.Set("st");
        auto usdPrimVarReaderVector2f = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/UsdPrimvarReader_float2"));
        usdPrimVarReaderVector2f.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPrimvarReader_float2")));
        auto varnameInput =
            usdPrimVarReaderVector2f.CreateInput(pxr::TfToken("varname"), pxr::SdfValueTypeNames->String);
        varnameInput.ConnectToSource(varnameHolderInput);
        UsdPrimVarReaderVector2fReader readerVector2fReader(usdPrimVarReaderVector2f, usdShadingNodeReadCache);

        auto primVarReaderVector2f = readerVector2fReader.read();

        REQUIRE(primVarReaderVector2f->primVarReaderType == PrimVarReaderType::UV);
    }

    SECTION("should read UsdPrimvarReader_float2 correctly for varname authored with no connection") {
        auto usdPrimVarReaderVector2f = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/UsdPrimvarReader_float2"));
        usdPrimVarReaderVector2f.CreateIdAttr(pxr::VtValue(pxr::TfToken("UsdPrimvarReader_float2")));
        usdPrimVarReaderVector2f.CreateInput(pxr::TfToken("varname"), pxr::SdfValueTypeNames->String).Set("st");
        UsdPrimVarReaderVector2fReader readerVector2fReader(usdPrimVarReaderVector2f, usdShadingNodeReadCache);

        auto primVarReaderVector2f = readerVector2fReader.read();

        REQUIRE(primVarReaderVector2f->primVarReaderType == PrimVarReaderType::UV);
    }
}
}