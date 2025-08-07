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
                                            IntersectorType::EMBREE, BucketSequenceType::SCANLINE,
                                            BucketSamplerType::ADAPTIVE, 0.007f, 8, true,
                                            RegionToRender(NDCRegion({0, 1}, {2, 3})), ImageFormatWriteOptions{});

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
        const pxr::GfVec4f regionToRender = UsdUtils::getStaticAttributeValueAs<pxr::GfVec4f>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("dataWindowNDC")));

        const pxr::TfToken openExrDataCompression = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("openExrCompression")));
        const pxr::TfToken openExrPixelType = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("openExrPixelType")));
        const pxr::TfToken openExrDataWindow = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(
            usdRenderSettings.GetPrim().GetAttribute(pxr::TfToken("openExrDataWindow")));

        REQUIRE(resolution == pxr::GfVec2i(1280, 720));
        REQUIRE(maxSamples == 4);
        REQUIRE(integratorType == pxr::TfToken("RAYTRACING"));
        REQUIRE(sampleCount == 8);
        REQUIRE(intersectorType == pxr::TfToken("EMBREE"));
        REQUIRE(bucketSequenceType == pxr::TfToken("SCANLINE"));
        REQUIRE(bucketSamplerType == pxr::TfToken("ADAPTIVE"));
        REQUIRE(adaptiveMaxError == 0.007f);
        REQUIRE(samplesPerAdaptivePass == 8);
        REQUIRE(useSpectralLensing == 1);
        REQUIRE(regionToRender[0] == 0);
        REQUIRE(regionToRender[1] == Catch::Detail::Approx(1.f));
        REQUIRE(regionToRender[2] == Catch::Detail::Approx(2.f));
        REQUIRE(regionToRender[3] == Catch::Detail::Approx(3.f));
        REQUIRE(openExrDataCompression == "ZIP_COMPRESSION");
        REQUIRE(openExrPixelType == "HALF");
        REQUIRE(openExrDataWindow == "WHOLE_IMAGE");
    }
}

}
