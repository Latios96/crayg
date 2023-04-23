#include "sceneIO/read/usd/UsdRenderSettingsReader.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdRender/settings.h>

namespace crayg {

TEST_CASE("UsdRenderSettingsReader::read") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdRenderSettings = pxr::UsdRenderSettings::Define(stage, pxr::SdfPath("/Render/settings"));

    SECTION("should read fully populated rendersettings") {
        usdRenderSettings.GetResolutionAttr().Set(pxr::GfVec2i(800, 600));
        usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("maxSamples"), pxr::SdfValueTypeNames->Int).Set(2);
        usdRenderSettings.GetPrim()
            .CreateAttribute(pxr::TfToken("integratorType"), pxr::SdfValueTypeNames->Token)
            .Set(pxr::TfToken("DEBUG"));
        usdRenderSettings.GetPrim()
            .CreateAttribute(pxr::TfToken("DEBUG:someToken"), pxr::SdfValueTypeNames->Token)
            .Set(pxr::TfToken("someTokenValue"));
        usdRenderSettings.GetPrim()
            .CreateAttribute(pxr::TfToken("intersectorType"), pxr::SdfValueTypeNames->Token)
            .Set(pxr::TfToken("EMBREE"));
        usdRenderSettings.GetPrim()
            .CreateAttribute(pxr::TfToken("bucketSequenceType"), pxr::SdfValueTypeNames->Token)
            .Set(pxr::TfToken("LINE_BY_LINE"));

        UsdRenderSettingsReader usdRenderSettingsReader(usdRenderSettings);
        auto renderSettings = usdRenderSettingsReader.read();

        REQUIRE(*renderSettings ==
                RenderSettings(crayg::Resolution(800, 600), 2, IntegratorType::DEBUG,
                               IntegratorSettings({{"DEBUG:someToken", {std::string("someTokenValue")}}}),
                               IntersectorType::EMBREE, BucketSequenceType::LINE_BY_LINE));
    }

    SECTION("should fallback to default values") {
        UsdRenderSettingsReader usdRenderSettingsReader(usdRenderSettings);
        auto renderSettings = usdRenderSettingsReader.read();

        REQUIRE(*renderSettings == RenderSettings::createDefault());
    }
}

}
