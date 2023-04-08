#include "fixtures/CameraLensFixtures.h"
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
                           IntegratorSettings({{"AMBIENT_OCCLUSION:sampleCount", {8}}}), IntersectorType::NAIVE_BVH);
        ImageMetadataCollector imageMetadataCollector;
        imageMetadataCollector.scene = &scene;
        ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::RENDER_SETTINGS_INTEGRATOR) == "RAYTRACING");
        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::RENDER_SETTINGS_INTERSECTOR) == "NAIVE_BVH");
        REQUIRE(imageMetadata.read<int>(ImageMetadataTokens::RENDER_SETTINGS_MAX_SAMPLES) == 4);
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

        ImageMetadataCollector imageMetadataCollector;
        imageMetadataCollector.scene = &scene;
        ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

        REQUIRE(imageMetadata.read<std::string>(ImageMetadataTokens::CAMERA_LENS_NAME) == scene.camera->getLens().name);
        REQUIRE(imageMetadata.read<int>(ImageMetadataTokens::CAMERA_LENS_ELEMENT_COUNT) ==
                scene.camera->getLens().elements.size());
        REQUIRE(imageMetadata.read<float>(ImageMetadataTokens::CAMERA_LENS_EFFECTIVE_FOCAL_LENGTH) ==
                Catch::Detail::Approx(72.1183792f));
    }
}

}