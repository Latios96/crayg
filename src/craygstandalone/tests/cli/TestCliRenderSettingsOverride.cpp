#include "craygstandalone/cli/CliRenderSettingsOverride.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("CliRenderSettingsOverride::hasAnyOverrides") {
    CliRenderSettingsOverride fullOverrides;
    fullOverrides.resolution = Resolution(800, 600);
    fullOverrides.maxSamples = 8;

    CliRenderSettingsOverride onlyResolution;
    onlyResolution.resolution = Resolution(800, 600);

    CliRenderSettingsOverride onlyMaxSamples;
    onlyMaxSamples.maxSamples = 8;

    CliRenderSettingsOverride onlyIntegrator;
    onlyIntegrator.integratorType = IntegratorType::DEBUG;

    CliRenderSettingsOverride onlyIntersector;
    onlyIntersector.intersectorType = IntersectorType::EMBREE;

    CliRenderSettingsOverride onlyTileSequenceType;
    onlyTileSequenceType.tileSequenceType = TileSequenceType::SCANLINE;

    CliRenderSettingsOverride onlyTileSamplerType;
    onlyTileSamplerType.tileSamplerType = TileSamplerType::UNIFORM;

    CliRenderSettingsOverride onlyAdaptiveMaxError;
    onlyAdaptiveMaxError.adaptiveMaxError = 0.1f;

    CliRenderSettingsOverride onlySamplesPerAdaptivePass;
    onlySamplesPerAdaptivePass.samplesPerAdaptivePass = 16;

    CliRenderSettingsOverride onlyIntegratorSettingsOverrides;
    onlyIntegratorSettingsOverrides.integratorSettingsOverrides.emplace_back("test", 1);

    SECTION("has overrides") {
        REQUIRE(fullOverrides.hasAnyOverrides());

        REQUIRE(onlyResolution.hasAnyOverrides());

        REQUIRE(onlyMaxSamples.hasAnyOverrides());

        REQUIRE(onlyIntegrator.hasAnyOverrides());

        REQUIRE(onlyIntersector.hasAnyOverrides());

        REQUIRE(onlyTileSequenceType.hasAnyOverrides());

        REQUIRE(onlyTileSamplerType.hasAnyOverrides());

        REQUIRE(onlyAdaptiveMaxError.hasAnyOverrides());

        REQUIRE(onlySamplesPerAdaptivePass.hasAnyOverrides());

        REQUIRE(onlyIntegratorSettingsOverrides.hasAnyOverrides());
    }

    SECTION("has no overrides") {
        REQUIRE_FALSE(CliRenderSettingsOverride().hasAnyOverrides());
    }
}

TEST_CASE("CliRenderSettingsOverride::reportOverrides") {
    CliRenderSettingsOverride fullOverrides;
    fullOverrides.resolution = Resolution(800, 600);
    fullOverrides.maxSamples = 8;
    fullOverrides.integratorType = IntegratorType::DEBUG;

    CliRenderSettingsOverride onlyResolution;
    onlyResolution.resolution = Resolution(800, 600);

    CliRenderSettingsOverride onlyMaxSamples;
    onlyMaxSamples.maxSamples = 8;

    CliRenderSettingsOverride onlyIntegratorType;
    onlyIntegratorType.integratorType = IntegratorType::DEBUG;

    CliRenderSettingsOverride onlyTileSequenceType;
    onlyTileSequenceType.tileSequenceType = TileSequenceType::SCANLINE;

    CliRenderSettingsOverride onlyTileSamplerType;
    onlyTileSamplerType.tileSamplerType = TileSamplerType::UNIFORM;

    CliRenderSettingsOverride onlyAdaptiveMaxError;
    onlyAdaptiveMaxError.adaptiveMaxError = 0.1f;

    CliRenderSettingsOverride onlySamplesPerAdaptivePass;
    onlySamplesPerAdaptivePass.samplesPerAdaptivePass = 16;

    CliRenderSettingsOverride onlyUseSpectralLensing;
    onlyUseSpectralLensing.useSpectralLensing = true;

    CliRenderSettingsOverride onlyIntegratorSettingsOverrides;
    onlyIntegratorSettingsOverrides.integratorSettingsOverrides.emplace_back("test", 1);

    SECTION("has overrides") {
        REQUIRE(fullOverrides.reportOverrides() ==
                R"(resolution -> 800x600, maxSamples -> 8, integratorType -> DEBUG)");

        REQUIRE(onlyResolution.reportOverrides() == "resolution -> 800x600");

        REQUIRE(onlyMaxSamples.reportOverrides() == "maxSamples -> 8");

        REQUIRE(onlyIntegratorType.reportOverrides() == R"(integratorType -> DEBUG)");

        REQUIRE(onlyTileSequenceType.reportOverrides() == R"(tileSequenceType -> LINE_BY_LINE)");

        REQUIRE(onlyTileSamplerType.reportOverrides() == R"(tileSamplerType -> UNIFORM)");

        REQUIRE(onlyAdaptiveMaxError.reportOverrides() == R"(adaptiveMaxError -> 0.1)");

        REQUIRE(onlySamplesPerAdaptivePass.reportOverrides() == R"(samplesPerAdaptivePass -> 16)");

        REQUIRE(onlyUseSpectralLensing.reportOverrides() == R"(useSpectralLensing -> true)");

        REQUIRE(onlyIntegratorSettingsOverrides.reportOverrides() == R"(test -> 1)");
    }

    SECTION("has no overrides") {
        REQUIRE(CliRenderSettingsOverride().reportOverrides().empty());
    }
}

TEST_CASE("CliRenderSettingsOverride::resolveOverrides") {
    CliRenderSettingsOverride fullOverrides;
    fullOverrides.resolution = Resolution(800, 600);
    fullOverrides.maxSamples = 8;
    fullOverrides.integratorType = IntegratorType::DEBUG;
    fullOverrides.tileSequenceType = TileSequenceType::SPIRAL;

    CliRenderSettingsOverride onlyResolution;
    onlyResolution.resolution = Resolution(800, 600);

    CliRenderSettingsOverride onlyMaxSamples;
    onlyMaxSamples.maxSamples = 8;

    CliRenderSettingsOverride onlyIntegratorType;
    onlyIntegratorType.integratorType = IntegratorType::DEBUG;

    CliRenderSettingsOverride onlyTileSequenceType;
    onlyTileSequenceType.tileSequenceType = TileSequenceType::SCANLINE;

    CliRenderSettingsOverride onlyTileSamplerType;
    onlyTileSamplerType.tileSamplerType = TileSamplerType::UNIFORM;

    CliRenderSettingsOverride onlyAdaptiveMaxError;
    onlyAdaptiveMaxError.adaptiveMaxError = 0.1f;

    CliRenderSettingsOverride onlySamplesPerAdaptivePass;
    onlySamplesPerAdaptivePass.samplesPerAdaptivePass = 16;

    RenderSettings renderSettings;
    renderSettings.resolution = Resolution(1280, 720);
    renderSettings.maxSamples = 4;
    renderSettings.integratorType = IntegratorType::RAYTRACING;

    CliRenderSettingsOverride onlyUseSpectralLensing;
    onlyUseSpectralLensing.useSpectralLensing = true;

    CliRenderSettingsOverride onlyIntegratorSettingsOverrides;
    onlyIntegratorSettingsOverrides.integratorSettingsOverrides.emplace_back("test", 1);

    CliRenderSettingsOverride onlyRegionToRender;
    onlyRegionToRender.regionToRender = RegionToRender(PixelRegion({0, 1}, {2, 3}));

    SECTION("has overrides") {
        REQUIRE(fullOverrides.resolveOverrides(renderSettings) ==
                RenderSettings({800, 600}, 8, IntegratorType::DEBUG, IntegratorSettings(), IntersectorType::EMBREE,
                               TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.007f, 8, false, std::nullopt,
                               ImageFormatWriteOptions{}));

        REQUIRE(onlyResolution.resolveOverrides(renderSettings) ==
                RenderSettings({800, 600}, 4, IntegratorType::RAYTRACING, IntegratorSettings(), IntersectorType::EMBREE,
                               TileSequenceType::SCANLINE, TileSamplerType::ADAPTIVE, 0.007f, 8, false, std::nullopt,
                               ImageFormatWriteOptions{}));

        REQUIRE(onlyMaxSamples.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 8, IntegratorType::RAYTRACING, IntegratorSettings(),
                               IntersectorType::EMBREE, TileSequenceType::SCANLINE, TileSamplerType::ADAPTIVE, 0.007f,
                               8, false, std::nullopt, ImageFormatWriteOptions{}));

        REQUIRE(onlyIntegratorType.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::DEBUG, IntegratorSettings(), IntersectorType::EMBREE,
                               TileSequenceType::SCANLINE, TileSamplerType::ADAPTIVE, 0.007f, 8, false, std::nullopt,
                               ImageFormatWriteOptions{}));

        REQUIRE(onlyTileSequenceType.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings(),
                               IntersectorType::EMBREE, TileSequenceType::SCANLINE, TileSamplerType::ADAPTIVE, 0.007f,
                               8, false, std::nullopt, ImageFormatWriteOptions{}));

        REQUIRE(onlyTileSamplerType.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings(),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::UNIFORM, 0.007f, 8,
                               false, std::nullopt, ImageFormatWriteOptions{}));

        REQUIRE(onlyAdaptiveMaxError.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings(),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.1f, 8,
                               false, std::nullopt, ImageFormatWriteOptions{}));

        REQUIRE(onlySamplesPerAdaptivePass.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings(),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.007f, 16,
                               false, std::nullopt, ImageFormatWriteOptions{}));

        REQUIRE(onlyUseSpectralLensing.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings(),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.007f, 8,
                               true, std::nullopt, ImageFormatWriteOptions{}));

        REQUIRE(onlyRegionToRender.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings(),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.007f, 8,
                               false, RegionToRender(PixelRegion({0, 1}, {2, 3})), ImageFormatWriteOptions{}));

        REQUIRE(onlyIntegratorSettingsOverrides.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings({{"test", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.007f, 8,
                               false, std::nullopt, ImageFormatWriteOptions{}));
    }

    SECTION("has no overrides") {
        REQUIRE(CliRenderSettingsOverride().resolveOverrides(renderSettings) == renderSettings);
    }
}

}