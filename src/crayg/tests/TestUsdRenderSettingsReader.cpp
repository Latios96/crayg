#include <catch2/catch.hpp>
#include "sceneIO/read/usd/UsdRenderSettingsReader.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdRender/settings.h>

namespace crayg {

TEST_CASE("UsdRenderSettingsReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdRenderSettings = pxr::UsdRenderSettings::Define(stage, pxr::SdfPath("/Render/settings"));

    SECTION("should read fully populated rendersettings") {
        usdRenderSettings.GetResolutionAttr().Set(pxr::GfVec2i(800, 600));
        usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("maxSamples"), pxr::SdfValueTypeNames->Int).Set(2);
        usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("integratorType"), pxr::SdfValueTypeNames->Token).Set(
            pxr::TfToken("DEBUG"));
        usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("DEBUG:someToken"), pxr::SdfValueTypeNames->Token).Set(
            pxr::TfToken("someTokenValue"));
        usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("intersectorType"), pxr::SdfValueTypeNames->Token).Set(
            pxr::TfToken("EMBREE"));

        UsdRenderSettingsReader usdRenderSettingsReader(usdRenderSettings);
        auto renderSettings = usdRenderSettingsReader.read();

        REQUIRE(*renderSettings == RenderSettings(crayg::Resolution(800, 600),
                                                  2,
                                                  IntegratorType::DEBUG,
                                                  IntegratorSettings({{"DEBUG:someToken",
                                                                       {std::string("someTokenValue")}}}),
                                                  IntersectorType::EMBREE));
    }

    SECTION("should fallback to default values") {
        UsdRenderSettingsReader usdRenderSettingsReader(usdRenderSettings);
        auto renderSettings = usdRenderSettingsReader.read();

        REQUIRE(*renderSettings == RenderSettings(crayg::Resolution(1280, 720),
                                                  4,
                                                  IntegratorType::RAYTRACING,
                                                  IntegratorSettings(), IntersectorType::EMBREE));
    }

    SECTION("should parse rendersettings case insensitive") {
        usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("integratorType"), pxr::SdfValueTypeNames->Token).Set(
            pxr::TfToken("DeBuG"));
        UsdRenderSettingsReader usdRenderSettingsReader(usdRenderSettings);
        auto renderSettings = usdRenderSettingsReader.read();

        REQUIRE(*renderSettings == RenderSettings(crayg::Resolution(1280, 720),
                                                  4,
                                                  IntegratorType::DEBUG,
                                                  IntegratorSettings(), IntersectorType::EMBREE));
    }

}

}
