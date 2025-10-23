#include "craygstandalone/cli/CliRenderSettingsOverride.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("CliRenderSettingsOverride::hasAnyOverrides") {
    CliRenderSettingsOverride fullOverrides;
    fullOverrides.resolution = Resolution(800, 600);
    fullOverrides.maxSamples = 8;

    SECTION("should have overrides") {
        REQUIRE(fullOverrides.hasAnyOverrides());
    }

    SECTION("should have override for only resolution") {
        CliRenderSettingsOverride onlyResolution;
        onlyResolution.resolution = Resolution(800, 600);

        REQUIRE(onlyResolution.hasAnyOverrides());
    }

    SECTION("should have override for only max samples") {
        CliRenderSettingsOverride onlyMaxSamples;
        onlyMaxSamples.maxSamples = 8;

        REQUIRE(onlyMaxSamples.hasAnyOverrides());
    }

    SECTION("should have override for only integrator") {
        CliRenderSettingsOverride onlyIntegrator;
        onlyIntegrator.integratorType = IntegratorType::DEBUG;

        REQUIRE(onlyIntegrator.hasAnyOverrides());
    }

    SECTION("should have override for only intersector") {
        CliRenderSettingsOverride onlyIntersector;
        onlyIntersector.intersectorType = IntersectorType::EMBREE;

        REQUIRE(onlyIntersector.hasAnyOverrides());
    }

    SECTION("should have override for only sequence type") {
        CliRenderSettingsOverride onlyTileSequenceType;
        onlyTileSequenceType.tileSequenceType = TileSequenceType::SCANLINE;

        REQUIRE(onlyTileSequenceType.hasAnyOverrides());
    }

    SECTION("should have override for only tile sampler type") {
        CliRenderSettingsOverride onlyTileSamplerType;
        onlyTileSamplerType.tileSamplerType = TileSamplerType::UNIFORM;

        REQUIRE(onlyTileSamplerType.hasAnyOverrides());
    }

    SECTION("should have override for only max adaptive error") {
        CliRenderSettingsOverride onlyAdaptiveMaxError;
        onlyAdaptiveMaxError.adaptiveMaxError = 0.1f;

        REQUIRE(onlyAdaptiveMaxError.hasAnyOverrides());
    }

    SECTION("should have override for only samples per adaptive pass") {
        CliRenderSettingsOverride onlySamplesPerAdaptivePass;
        onlySamplesPerAdaptivePass.samplesPerAdaptivePass = 16;

        REQUIRE(onlySamplesPerAdaptivePass.hasAnyOverrides());
    }

    SECTION("should have override for only integrator setting overrides") {
        CliRenderSettingsOverride onlyIntegratorSettingsOverrides;
        onlyIntegratorSettingsOverrides.integratorSettingsOverrides.emplace_back("test", 1);

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

    SECTION("report full overrides") {
        REQUIRE(fullOverrides.reportOverrides() ==
                R"(resolution -> 800x600, maxSamples -> 8, integratorType -> DEBUG)");
    }

    SECTION("should report resolution override") {
        CliRenderSettingsOverride onlyResolution;
        onlyResolution.resolution = Resolution(800, 600);

        REQUIRE(onlyResolution.reportOverrides() == "resolution -> 800x600");
    }

    SECTION("should report max samples override") {
        CliRenderSettingsOverride onlyMaxSamples;
        onlyMaxSamples.maxSamples = 8;

        REQUIRE(onlyMaxSamples.reportOverrides() == "maxSamples -> 8");
    }

    SECTION("should report integrator type override") {
        CliRenderSettingsOverride onlyIntegratorType;
        onlyIntegratorType.integratorType = IntegratorType::DEBUG;

        REQUIRE(onlyIntegratorType.reportOverrides() == R"(integratorType -> DEBUG)");
    }

    SECTION("should report tile sequence type override") {
        CliRenderSettingsOverride onlyTileSequenceType;
        onlyTileSequenceType.tileSequenceType = TileSequenceType::SCANLINE;

        REQUIRE(onlyTileSequenceType.reportOverrides() == R"(tileSequenceType -> SCANLINE)");
    }

    SECTION("should report tile sampler type override") {
        CliRenderSettingsOverride onlyTileSamplerType;
        onlyTileSamplerType.tileSamplerType = TileSamplerType::UNIFORM;

        REQUIRE(onlyTileSamplerType.reportOverrides() == R"(tileSamplerType -> UNIFORM)");
    }

    SECTION("should report adaptive max error override") {
        CliRenderSettingsOverride onlyAdaptiveMaxError;
        onlyAdaptiveMaxError.adaptiveMaxError = 0.1f;

        REQUIRE(onlyAdaptiveMaxError.reportOverrides() == R"(adaptiveMaxError -> 0.1)");
    }

    SECTION("should report samples per adaptive pass override") {
        CliRenderSettingsOverride onlySamplesPerAdaptivePass;
        onlySamplesPerAdaptivePass.samplesPerAdaptivePass = 16;

        REQUIRE(onlySamplesPerAdaptivePass.reportOverrides() == R"(samplesPerAdaptivePass -> 16)");
    }

    SECTION("should report use spectral lensing override") {
        CliRenderSettingsOverride onlyUseSpectralLensing;
        onlyUseSpectralLensing.useSpectralLensing = true;

        REQUIRE(onlyUseSpectralLensing.reportOverrides() == R"(useSpectralLensing -> true)");
    }

    SECTION("should report integrator settings override") {
        CliRenderSettingsOverride onlyIntegratorSettingsOverrides;
        onlyIntegratorSettingsOverrides.integratorSettingsOverrides.emplace_back("test", 1);

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

    RenderSettings renderSettings;
    renderSettings.resolution = Resolution(1280, 720);
    renderSettings.maxSamples = 4;
    renderSettings.integratorType = IntegratorType::RAYTRACING;
    renderSettings.integratorSettings.settings["myValue"] = 1;

    SECTION("should resolve full overrides") {
        REQUIRE(fullOverrides.resolveOverrides(renderSettings) ==
                RenderSettings({800, 600}, 8, IntegratorType::DEBUG, IntegratorSettings({{"myValue", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.007f, 8,
                               false, std::nullopt, ImageFormatWriteOptions{}));
    }

    SECTION("should resolve only resolution override") {
        CliRenderSettingsOverride onlyResolution;
        onlyResolution.resolution = Resolution(800, 600);

        REQUIRE(onlyResolution.resolveOverrides(renderSettings) ==
                RenderSettings({800, 600}, 4, IntegratorType::RAYTRACING, IntegratorSettings({{"myValue", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SCANLINE, TileSamplerType::ADAPTIVE, 0.007f,
                               8, false, std::nullopt, ImageFormatWriteOptions{}));
    }

    SECTION("should resolve only max samples override") {
        CliRenderSettingsOverride onlyMaxSamples;
        onlyMaxSamples.maxSamples = 8;

        REQUIRE(onlyMaxSamples.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 8, IntegratorType::RAYTRACING, IntegratorSettings({{"myValue", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SCANLINE, TileSamplerType::ADAPTIVE, 0.007f,
                               8, false, std::nullopt, ImageFormatWriteOptions{}));
    }

    SECTION("should resolve only integrator type override") {
        CliRenderSettingsOverride onlyIntegratorType;
        onlyIntegratorType.integratorType = IntegratorType::DEBUG;

        REQUIRE(onlyIntegratorType.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::DEBUG, IntegratorSettings({{"myValue", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SCANLINE, TileSamplerType::ADAPTIVE, 0.007f,
                               8, false, std::nullopt, ImageFormatWriteOptions{}));
    }

    SECTION("should resolve only tile sequence type override") {
        CliRenderSettingsOverride onlyTileSequenceType;
        onlyTileSequenceType.tileSequenceType = TileSequenceType::SCANLINE;

        REQUIRE(onlyTileSequenceType.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings({{"myValue", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SCANLINE, TileSamplerType::ADAPTIVE, 0.007f,
                               8, false, std::nullopt, ImageFormatWriteOptions{}));
    }

    SECTION("should resolve only tile sampler type override") {
        CliRenderSettingsOverride onlyTileSamplerType;
        onlyTileSamplerType.tileSamplerType = TileSamplerType::UNIFORM;

        REQUIRE(onlyTileSamplerType.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings({{"myValue", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::UNIFORM, 0.007f, 8,
                               false, std::nullopt, ImageFormatWriteOptions{}));
    }

    SECTION("should resolve only max adaptive error override") {
        CliRenderSettingsOverride onlyAdaptiveMaxError;
        onlyAdaptiveMaxError.adaptiveMaxError = 0.1f;

        REQUIRE(onlyAdaptiveMaxError.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings({{"myValue", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.1f, 8,
                               false, std::nullopt, ImageFormatWriteOptions{}));
    }

    SECTION("should resolve only samples per adaptive pass override") {
        CliRenderSettingsOverride onlySamplesPerAdaptivePass;
        onlySamplesPerAdaptivePass.samplesPerAdaptivePass = 16;

        REQUIRE(onlySamplesPerAdaptivePass.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings({{"myValue", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.007f, 16,
                               false, std::nullopt, ImageFormatWriteOptions{}));
    }

    SECTION("should resolve only spectral lensing override") {
        CliRenderSettingsOverride onlyUseSpectralLensing;
        onlyUseSpectralLensing.useSpectralLensing = true;

        REQUIRE(onlyUseSpectralLensing.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings({{"myValue", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.007f, 8,
                               true, std::nullopt, ImageFormatWriteOptions{}));
    }

    SECTION("should resolve only integrator settings override") {
        CliRenderSettingsOverride onlyIntegratorSettingsOverrides;
        onlyIntegratorSettingsOverrides.integratorSettingsOverrides.emplace_back("test", 1);

        REQUIRE(onlyIntegratorSettingsOverrides.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING,
                               IntegratorSettings({{"test", 1}, {"myValue", 1}}), IntersectorType::EMBREE,
                               TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.007f, 8, false, std::nullopt,
                               ImageFormatWriteOptions{}));
    }
    SECTION("should resolve only render region override") {
        CliRenderSettingsOverride onlyRegionToRender;
        onlyRegionToRender.regionToRender = RegionToRender(PixelRegion({0, 1}, {2, 3}));

        REQUIRE(onlyRegionToRender.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings({{"myValue", 1}}),
                               IntersectorType::EMBREE, TileSequenceType::SPIRAL, TileSamplerType::ADAPTIVE, 0.007f, 8,
                               false, RegionToRender(PixelRegion({0, 1}, {2, 3})), ImageFormatWriteOptions{}));
    }

    SECTION("has no overrides") {
        REQUIRE(CliRenderSettingsOverride().resolveOverrides(renderSettings) == renderSettings);
    }
}

}