#include <catch2/catch.hpp>
#include "sceneIO/write/usd/UsdRenderSettingsWriter.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdRender/settings.h>

namespace crayg {

TEST_CASE("UsdRenderSettingsWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should write rendersettings correctly") {
        RenderSettings renderSettings(Resolution(1280, 720), 4);

        UsdRenderSettingsWriter usdRenderSettingsWriter(renderSettings);
        usdRenderSettingsWriter.write(stage);

        auto usdRenderSettings = pxr::UsdRenderSettings(stage->GetPrimAtPath(pxr::SdfPath("/Render/settings")));
        const pxr::GfVec2i
            resolution = UsdUtils::getAttributeValueAs<pxr::GfVec2i>(usdRenderSettings.GetResolutionAttr());
        int maxSamples =
            UsdUtils::getAttributeValueAs<int>(usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("maxSamples")));
        REQUIRE(resolution == pxr::GfVec2i(1280, 720));
        REQUIRE(maxSamples == 4);
    }

}

}
