#include "fixtures/CameraLensFixtures.h"
#include "scene/primitives/Sphere.h"
#include "utils/ImageMetadataCollector.h"
#include <catch2/catch.hpp>

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
        REQUIRE(imageMetadata.read<std::chrono::seconds>(ImageMetadataTokens::RENDER_TIME_SECONDS) ==
                std::chrono::seconds(5));
    }

    SECTION("should collect render settings") {
        Scene scene;
        scene.renderSettings =
            RenderSettings(Resolution(1280, 720), 4, IntegratorType::RAYTRACING,
                           IntegratorSettings({{"AMBIENT_OCCLUSION:sampleCount", {8}}}), IntersectorType::EMBREE,
                           BucketSequenceType::LINE_BY_LINE, BucketSamplerType::ADAPTIVE, 0.007f, 8, false);
        ImageMetadataCollector imageMetadataCollector;
        imageMetadataCollector.scene = &scene;
        ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::RENDER_SETTINGS_INTEGRATOR) == "RAYTRACING");
        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::RENDER_SETTINGS_INTERSECTOR) == "EMBREE");
        REQUIRE(imageMetadata.read<int>(ImageMetadataTokens::RENDER_SETTINGS_MAX_SAMPLES) == 4);
        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::RENDER_SETTINGS_BUCKET_SEQUENCE_TYPE) ==
                "LINE_BY_LINE");
        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::RENDER_SETTINGS_BUCKET_SAMPLER_TYPE) ==
                "ADAPTIVE");
        REQUIRE(imageMetadata.read<float>(ImageMetadataTokens::RENDER_SETTINGS_ADAPTIVE_MAX_ERROR) == 0.007f);
        REQUIRE(imageMetadata.read<int>(ImageMetadataTokens::RENDER_SETTINGS_SAMPLES_PER_ADAPTIVE_PASS) == 8);
        REQUIRE(imageMetadata.read<int>(ImageMetadataTokens::RENDER_SETTINGS_USE_SPECTRAL_LENSING) == 0);
        REQUIRE(imageMetadata.read<int>("crayg/renderSettings/integratorSettings/AMBIENT_OCCLUSION:sampleCount") == 8);
    }

    SECTION("should collect normal camera parameters") {
        Scene scene;
        scene.camera = std::make_shared<crayg::Camera>(Transform::withPosition({1.f, 2.f, -3.f}), 35.f, 36.f);
        scene.camera->setName("/usdCamera");
        scene.camera->setFocusDistance(50.f);
        scene.camera->setFStop(2.8f);
        scene.camera->setCameraType(CameraType::THIN_LENS);

        ImageMetadataCollector imageMetadataCollector;
        imageMetadataCollector.scene = &scene;
        ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::CAMERA_NAME) == scene.camera->getName());
        REQUIRE(imageMetadata.read<float>(ImageMetadataTokens::CAMERA_FOCAL_LENGTH) == scene.camera->getFocalLength());
        REQUIRE(imageMetadata.read<float>(ImageMetadataTokens::CAMERA_FILM_BACK_SIZE) ==
                scene.camera->getFilmbackSize());
        REQUIRE(imageMetadata.read<float>(ImageMetadataTokens::CAMERA_FOCUS_DISTANCE) ==
                scene.camera->getFocusDistance());
        REQUIRE(imageMetadata.read<float>(ImageMetadataTokens::CAMERA_F_STOP) == scene.camera->getFStop());
        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::CAMERA_CAMERA_TYPE) ==
                fmt::format("{}", scene.camera->getCameraType()));
    }

    SECTION("should collect realistic camera parameters") {
        Scene scene;
        scene.camera = std::make_shared<crayg::Camera>(Transform::withPosition({1.f, 2.f, -3.f}), 35.f, 36.f);
        scene.camera->setName("/usdCamera");
        scene.camera->setFocusDistance(50.f);
        scene.camera->setFStop(2.8f);
        scene.camera->setCameraType(CameraType::REALISTIC);
        scene.camera->lens = std::make_unique<CameraLens>(CameraLensFixtures::createCanon70_200mm());
        scene.camera->lens->metadata.squeeze = 2;
        scene.camera->lens->metadata.patent = "US 132";
        scene.camera->lens->metadata.description = "A Canon Lens";

        ImageMetadataCollector imageMetadataCollector;
        imageMetadataCollector.scene = &scene;
        ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::CAMERA_LENS_NAME) ==
                scene.camera->getLens().metadata.name);
        REQUIRE(imageMetadata.read<int>(ImageMetadataTokens::CAMERA_LENS_ELEMENT_COUNT) ==
                scene.camera->getLens().elements.size());
        REQUIRE(imageMetadata.read<float>(ImageMetadataTokens::CAMERA_LENS_EFFECTIVE_FOCAL_LENGTH) ==
                Catch::Detail::Approx(71.64062f));
        REQUIRE(imageMetadata.read<float>(ImageMetadataTokens::CAMERA_LENS_MAXIMUM_F_NUMBER) ==
                Catch::Detail::Approx(3.41146f));
        REQUIRE(imageMetadata.read<int>(ImageMetadataTokens::CAMERA_LENS_IS_ANAMORPHIC) == 0);
        REQUIRE(imageMetadata.read<float>(ImageMetadataTokens::CAMERA_LENS_SQUEEZE) == 2);
        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::CAMERA_LENS_PATENT) == "US 132");
        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::CAMERA_LENS_DESCRIPTION) == "A Canon Lens");
    }

    SECTION("should collect scene stats") {
        Scene scene;
        scene.addObject(std::make_shared<Sphere>());

        ImageMetadataCollector imageMetadataCollector;
        imageMetadataCollector.scene = &scene;
        ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

        REQUIRE(imageMetadata.read<int>(ImageMetadataTokens::SCENE_STATS_OBJECT_COUNT) == 1);
        REQUIRE(imageMetadata.read<int>(ImageMetadataTokens::SCENE_STATS_PRIMITIVE_COUNT) == 1);
    }
}

}