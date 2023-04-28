#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/UsdRenderSettingsWriter.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdRender/settings.h>

namespace crayg {

TEST_CASE("UsdRenderSettingsWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should write rendersettings correctly") {
        RenderSettings renderSettings(Resolution(1280, 720), 4, IntegratorType::RAYTRACING,
                                      IntegratorSettings({{"AMBIENT_OCCLUSION:sampleCount", {8}}}),
                                      IntersectorType::EMBREE, BucketSequenceType::LINE_BY_LINE);

        UsdRenderSettingsWriter usdRenderSettingsWriter(renderSettings);
        usdRenderSettingsWriter.write(stage);

        auto usdRenderSettings = pxr::UsdRenderSettings(stage->GetPrimAtPath(pxr::SdfPath("/Render/settings")));
        const pxr::GfVec2i resolution =
            UsdUtils::getStaticAttributeValueAs<pxr::GfVec2i>(usdRenderSettings.GetResolutionAttr());
        int maxSamples = UsdUtils::getStaticAttributeValueAs<int>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("maxSamples")));
        pxr::TfToken integratorType = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("integratorType")));
        const int sampleCount = UsdUtils::getStaticAttributeValueAs<int>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("AMBIENT_OCCLUSION:sampleCount")));
        pxr::TfToken intersectorType = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("intersectorType")));
        pxr::TfToken bucketSequenceType = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("bucketSequenceType")));
        REQUIRE(resolution == pxr::GfVec2i(1280, 720));
        REQUIRE(maxSamples == 4);
        REQUIRE(integratorType == pxr::TfToken("RAYTRACING"));
        REQUIRE(sampleCount == 8);
        REQUIRE(intersectorType == pxr::TfToken("EMBREE"));
        REQUIRE(bucketSequenceType == pxr::TfToken("LINE_BY_LINE"));
    }
}

}
