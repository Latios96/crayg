#include <catch2/catch.hpp>
#include "sceneIO/read/usd/UsdRenderSettingsTranslator.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdRender/settings.h>

namespace crayg {

TEST_CASE("UsdRenderSettingsTranslator::translate") {
    auto stage = pxr::UsdStage::CreateInMemory();
    auto usdRenderSettings = pxr::UsdRenderSettings::Define(stage, pxr::SdfPath("/Render/settings"));

    SECTION("should translate fully populated rendersettings") {
        usdRenderSettings.GetResolutionAttr().Set(pxr::GfVec2i(800, 600));
        usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("maxSamples"), pxr::SdfValueTypeNames->Int).Set(2);

        UsdRenderSettingsTranslator usdRenderSettingsTranslator(usdRenderSettings);
        auto renderSettings = usdRenderSettingsTranslator.translate();

        REQUIRE(*renderSettings == RenderSettings(crayg::Resolution(800, 600), 2));
    }

    SECTION("should fallback to default values") {
        UsdRenderSettingsTranslator usdRenderSettingsTranslator(usdRenderSettings);
        auto renderSettings = usdRenderSettingsTranslator.translate();

        REQUIRE(*renderSettings == RenderSettings(crayg::Resolution(1280, 720), 4));
    }

}

}
