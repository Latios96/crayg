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

        UsdRenderSettingsReader usdRenderSettingsReader(usdRenderSettings);
        auto renderSettings = usdRenderSettingsReader.read();

        REQUIRE(*renderSettings == RenderSettings(crayg::Resolution(800, 600), 2));
    }

    SECTION("should fallback to default values") {
        UsdRenderSettingsReader usdRenderSettingsReader(usdRenderSettings);
        auto renderSettings = usdRenderSettingsReader.read();

        REQUIRE(*renderSettings == RenderSettings(crayg::Resolution(1280, 720), 4));
    }

}

}
