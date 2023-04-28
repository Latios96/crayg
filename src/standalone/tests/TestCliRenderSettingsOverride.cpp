#include "CliRenderSettingsOverride.h"
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

    SECTION("has overrides") {
        REQUIRE(fullOverrides.hasAnyOverrides());

        REQUIRE(onlyResolution.hasAnyOverrides());

        REQUIRE(onlyMaxSamples.hasAnyOverrides());

        REQUIRE(onlyIntegrator.hasAnyOverrides());

        REQUIRE(onlyIntersector.hasAnyOverrides());
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
        REQUIRE(fullOverrides.reportOverrides() ==
                R"(resolution -> 800x600, maxSamples -> 8, integratorType -> "DEBUG")");

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
    fullOverrides.bucketSequenceType = BucketSequenceType::SPIRAL;

    CliRenderSettingsOverride onlyResolution;
    onlyResolution.resolution = Resolution(800, 600);

    CliRenderSettingsOverride onlyMaxSamples;
    onlyMaxSamples.maxSamples = 8;

    CliRenderSettingsOverride onlyIntegratorType;
    onlyIntegratorType.integratorType = IntegratorType::DEBUG;

    CliRenderSettingsOverride onlyBucketSequenceType;
    onlyBucketSequenceType.bucketSequenceType = BucketSequenceType::SPIRAL;

    RenderSettings renderSettings;
    renderSettings.resolution = Resolution(1280, 720);
    renderSettings.maxSamples = 4;
    renderSettings.integratorType = IntegratorType::RAYTRACING;

    SECTION("has overrides") {
        REQUIRE(fullOverrides.resolveOverrides(renderSettings) ==
                RenderSettings({800, 600}, 8, IntegratorType::DEBUG, IntegratorSettings(), IntersectorType::EMBREE,
                               BucketSequenceType::SPIRAL));

        REQUIRE(onlyResolution.resolveOverrides(renderSettings) ==
                RenderSettings({800, 600}, 4, IntegratorType::RAYTRACING, IntegratorSettings(), IntersectorType::EMBREE,
                               BucketSequenceType::LINE_BY_LINE));

        REQUIRE(onlyMaxSamples.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 8, IntegratorType::RAYTRACING, IntegratorSettings(),
                               IntersectorType::EMBREE, BucketSequenceType::LINE_BY_LINE));

        REQUIRE(onlyIntegratorType.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::DEBUG, IntegratorSettings(), IntersectorType::EMBREE,
                               BucketSequenceType::LINE_BY_LINE));

        REQUIRE(onlyBucketSequenceType.resolveOverrides(renderSettings) ==
                RenderSettings({1280, 720}, 4, IntegratorType::RAYTRACING, IntegratorSettings(),
                               IntersectorType::EMBREE, BucketSequenceType::SPIRAL));
    }

    SECTION("has no overrides") {
        REQUIRE(CliRenderSettingsOverride().resolveOverrides(renderSettings) == renderSettings);
    }
}

}