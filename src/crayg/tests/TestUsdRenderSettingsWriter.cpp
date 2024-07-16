#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/UsdRenderSettingsWriter.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdRender/settings.h>

namespace crayg {

TEST_CASE("UsdRenderSettingsWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();

    SECTION("should write rendersettings correctly") {
        const RenderSettings renderSettings(Resolution(1280, 720), 4, IntegratorType::RAYTRACING,
                                            IntegratorSettings({{"AMBIENT_OCCLUSION:sampleCount", {8}}}),
                                            IntersectorType::EMBREE, BucketSequenceType::LINE_BY_LINE,
                                            BucketSamplerType::ADAPTIVE, 0.007f, 8, true, Bounds2di({0, 1}, {2, 3}));

        UsdRenderSettingsWriter usdRenderSettingsWriter(renderSettings);
        usdRenderSettingsWriter.write(stage);

        const auto usdRenderSettings = pxr::UsdRenderSettings(stage->GetPrimAtPath(pxr::SdfPath("/Render/settings")));
        const pxr::GfVec2i resolution =
            UsdUtils::getStaticAttributeValueAs<pxr::GfVec2i>(usdRenderSettings.GetResolutionAttr());
        const int maxSamples = UsdUtils::getStaticAttributeValueAs<int>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("maxSamples")));
        const pxr::TfToken integratorType = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("integratorType")));
        const int sampleCount = UsdUtils::getStaticAttributeValueAs<int>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("AMBIENT_OCCLUSION:sampleCount")));
        const pxr::TfToken intersectorType = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("intersectorType")));
        const pxr::TfToken bucketSequenceType = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("bucketSequenceType")));
        const pxr::TfToken bucketSamplerType = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("bucketSamplerType")));
        const float adaptiveMaxError = UsdUtils::getStaticAttributeValueAs<float>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("adaptiveMaxError")));
        const int samplesPerAdaptivePass = UsdUtils::getStaticAttributeValueAs<int>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("samplesPerAdaptivePass")));
        const int useSpectralLensing = UsdUtils::getStaticAttributeValueAs<int>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("useSpectralLensing")));
        const pxr::GfVec4i regionToRender = UsdUtils::getStaticAttributeValueAs<pxr::GfVec4i>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("regionToRender")));
        REQUIRE(resolution == pxr::GfVec2i(1280, 720));
        REQUIRE(maxSamples == 4);
        REQUIRE(integratorType == pxr::TfToken("RAYTRACING"));
        REQUIRE(sampleCount == 8);
        REQUIRE(intersectorType == pxr::TfToken("EMBREE"));
        REQUIRE(bucketSequenceType == pxr::TfToken("LINE_BY_LINE"));
        REQUIRE(bucketSamplerType == pxr::TfToken("ADAPTIVE"));
        REQUIRE(adaptiveMaxError == 0.007f);
        REQUIRE(samplesPerAdaptivePass == 8);
        REQUIRE(useSpectralLensing == 1);
        REQUIRE(regionToRender == pxr::GfVec4i(0, 1, 2, 3));
    }
}

}
