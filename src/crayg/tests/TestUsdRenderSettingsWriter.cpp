#include <catch2/catch.hpp>
#include "sceneIO/write/usd/UsdRenderSettingsWriter.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdRender/settings.h>

namespace crayg {

TEST_CASE("UsdRenderSettingsWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should write rendersettings correctly") {
        RenderSettings renderSettings
            (Resolution(1280, 720), 4, IntegratorType::RAYTRACING, IntegratorSettings({{"AMBIENT_OCCLUSION:sampleCount",
                                                                                        {8}}}));

        UsdRenderSettingsWriter usdRenderSettingsWriter(renderSettings);
        usdRenderSettingsWriter.write(stage);

        auto usdRenderSettings = pxr::UsdRenderSettings(stage->GetPrimAtPath(pxr::SdfPath("/Render/settings")));
        const pxr::GfVec2i
            resolution = UsdUtils::getAttributeValueAs<pxr::GfVec2i>(usdRenderSettings.GetResolutionAttr());
        int maxSamples =
            UsdUtils::getAttributeValueAs<int>(usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("maxSamples")));
        pxr::TfToken integratorType =
            UsdUtils::getAttributeValueAs<pxr::TfToken>(usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken(
                "integratorType")));
        const int sampleCount =
            UsdUtils::getAttributeValueAs<int>(usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken(
                "AMBIENT_OCCLUSION:sampleCount")));
        REQUIRE(resolution == pxr::GfVec2i(1280, 720));
        REQUIRE(maxSamples == 4);
        REQUIRE(integratorType == pxr::TfToken("RAYTRACING"));
        REQUIRE(sampleCount == 8);
    }

}

}
