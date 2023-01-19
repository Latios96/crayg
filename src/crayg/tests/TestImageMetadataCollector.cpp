#include <catch2/catch.hpp>
#include "utils/ImageMetadataCollector.h"

namespace crayg {

TEST_CASE("TestImageMetadataCollector::collect") {


    SECTION("should collect only basic metadata") {
        ImageMetadataCollector imageMetadataCollector;

        ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

        REQUIRE_FALSE(imageMetadata.read<std::string>(ImageMetadataTokens::CRAYG_VERSION).empty());
        REQUIRE_FALSE(imageMetadata.read<std::string>(ImageMetadataTokens::CPU).empty());
        REQUIRE_FALSE(imageMetadata.has(ImageMetadataTokens::RENDER_TIME));
        REQUIRE_FALSE(imageMetadata.has(ImageMetadataTokens::RENDER_SETTINGS_INTEGRATOR));
    }

    SECTION("should collect render time") {
        ImageMetadataCollector imageMetadataCollector;
        imageMetadataCollector.renderTime = std::chrono::seconds(5);

        ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::RENDER_TIME) == "00:00:05");
        REQUIRE(imageMetadata.read<std::chrono::seconds>(ImageMetadataTokens::RENDER_TIME_SECONDS)
                    == std::chrono::seconds(5));
    }

    SECTION("should collect render settings") {

        RenderSettings renderSettings
            (Resolution(1280, 720),
             4,
             IntegratorType::RAYTRACING,
             IntegratorSettings({{"AMBIENT_OCCLUSION:sampleCount",
                                  {8}}}),
             IntersectorType::NAIVE_BVH);
        ImageMetadataCollector imageMetadataCollector;
        imageMetadataCollector.renderSettings = renderSettings;
        ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::RENDER_SETTINGS_INTEGRATOR) == "RAYTRACING");
        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::RENDER_SETTINGS_INTERSECTOR) == "NAIVE_BVH");
        REQUIRE(imageMetadata.read<int>(ImageMetadataTokens::RENDER_SETTINGS_MAX_SAMPLES) == 4);
        REQUIRE(imageMetadata.read<int>("crayg/renderSettings/integratorSettings/AMBIENT_OCCLUSION:sampleCount") == 8);
    }

}

}