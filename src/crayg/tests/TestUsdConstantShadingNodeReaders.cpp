#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdConstantShadingNodeReaders.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

TEST_CASE("TestUsdFloatConstantReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdFloatConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/FloatConstant"));
    usdFloatConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:FloatConstant")));
    usdFloatConstant.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Float).Set(0.1f);

    SECTION("should read correctly") {
        UsdFloatConstantReader usdFloatConstantReader(usdFloatConstant);

        auto floatConstant = usdFloatConstantReader.read();

        REQUIRE(floatConstant->value == 0.1f);
    }
}

TEST_CASE("TestUsdIntConstantReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdIntConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/IntConstant"));
    usdIntConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:IntConstant")));
    usdIntConstant.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Int).Set(1);

    SECTION("should read correctly") {
        UsdIntConstantReader usdIntConstantReader(usdIntConstant);

        auto IntConstant = usdIntConstantReader.read();

        REQUIRE(IntConstant->value == 1);
    }
}

TEST_CASE("TestUsdVector2fConstantReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdVector2fConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/Vector2fConstant"));
    usdVector2fConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:Vector2fConstant")));
    usdVector2fConstant.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Float2).Set(pxr::GfVec2f(1, 2));

    SECTION("should read correctly") {
        UsdVector2fConstantReader usdVector2fConstantReader(usdVector2fConstant);

        auto Vector2fConstant = usdVector2fConstantReader.read();

        REQUIRE(Vector2fConstant->value == Vector2f(1, 2));
    }
}

TEST_CASE("TestUsdColorConstantReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdColorConstant = pxr::UsdShadeShader::Define(stage, pxr::SdfPath("/ColorConstant"));
    usdColorConstant.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:ColorConstant")));
    usdColorConstant.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Vector3f).Set(pxr::GfVec3f(1, 2, 3));

    SECTION("should read correctly") {
        UsdColorConstantReader usdColorConstantReader(usdColorConstant);

        auto ColorConstant = usdColorConstantReader.read();

        REQUIRE(ColorConstant->value == Color(1, 2, 3));
    }
}

}