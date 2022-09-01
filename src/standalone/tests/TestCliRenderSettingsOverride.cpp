#include <catch2/catch.hpp>
#include "CliRenderSettingsOverride.h"

namespace crayg {

TEST_CASE("CliRenderSettingsOverride::hasAnyOverrides") {
    CliRenderSettingsOverride fullOverrides;
    fullOverrides.resolution = Resolution(800, 600);
    fullOverrides.maxSamples = 8;

    CliRenderSettingsOverride onlyResolution;
    onlyResolution.resolution = Resolution(800, 600);

    CliRenderSettingsOverride onlyMaxSamples;
    onlyMaxSamples.maxSamples = 8;

    SECTION("has overrides") {

        REQUIRE(fullOverrides.hasAnyOverrides());

        REQUIRE(onlyResolution.hasAnyOverrides());

        REQUIRE(onlyMaxSamples.hasAnyOverrides());
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

    SECTION("has overrides") {
        REQUIRE(
            fullOverrides.reportOverrides() == R"(resolution -> 800x600, maxSamples -> 8, integratorType -> "DEBUG")");

        REQUIRE(onlyResolution.reportOverrides() == "resolution -> 800x600");

        REQUIRE(onlyMaxSamples.reportOverrides() == "maxSamples -> 8");

        REQUIRE(onlyIntegratorType.reportOverrides() == R"(integratorType -> "DEBUG")");
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

    CliRenderSettingsOverride onlyResolution;
    onlyResolution.resolution = Resolution(800, 600);

    CliRenderSettingsOverride onlyMaxSamples;
    onlyMaxSamples.maxSamples = 8;

    CliRenderSettingsOverride onlyIntegratorType;
    onlyIntegratorType.integratorType = IntegratorType::DEBUG;

    RenderSettings renderSettings;
    renderSettings.resolution = Resolution(1280, 720);
    renderSettings.maxSamples = 4;
    renderSettings.integratorType = IntegratorType::RAYTRACING;

    SECTION("has overrides") {
        REQUIRE(fullOverrides.resolveOverrides(renderSettings) == RenderSettings({800, 600},
                                                                                 8,
                                                                                 IntegratorType::DEBUG,
                                                                                 IntegratorSettings()));

        REQUIRE(onlyResolution.resolveOverrides(renderSettings)
                    == RenderSettings({800, 600}, 4, IntegratorType::RAYTRACING, IntegratorSettings()));

        REQUIRE(onlyMaxSamples.resolveOverrides(renderSettings)
                    == RenderSettings({1280, 720}, 8, IntegratorType::RAYTRACING, IntegratorSettings()));

        REQUIRE(onlyIntegratorType.resolveOverrides(renderSettings)
                    == RenderSettings({1280, 720}, 4, IntegratorType::DEBUG, IntegratorSettings()));
    }

    SECTION("has no overrides") {
        REQUIRE(CliRenderSettingsOverride().resolveOverrides(renderSettings) == renderSettings);
    }
}

}