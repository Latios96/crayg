#include "ImageMetadataCollector.h"
#include "../CraygInfo.h"
#include <cpuinfo.h>
#include <fmt/chrono.h>

namespace crayg {

ImageMetadataCollector::ImageMetadataCollector() {
}

ImageMetadataCollector::ImageMetadataCollector(const std::optional<std::chrono::seconds> &renderTime, Scene *scene)
    : renderTime(renderTime), scene(scene) {
}

ImageMetadata ImageMetadataCollector::collectMetadata() {
    ImageMetadata imageMetadata;

    collectCraygVersion(imageMetadata);
    collectCpuName(imageMetadata);
    collectRenderTimeIfPresent(imageMetadata);
    collectRenderSettingsIfPresent(imageMetadata);
    collectCamera(imageMetadata);
    collectSceneStats(imageMetadata);

    return imageMetadata;
}

void ImageMetadataCollector::collectCraygVersion(ImageMetadata &imageMetadata) const {
    imageMetadata.write(ImageMetadataTokens::CRAYG_VERSION,
                        fmt::format("{}-{}", CraygInfo::VERSION, CraygInfo::COMMIT_HASH));
}

void ImageMetadataCollector::collectCpuName(ImageMetadata &imageMetadata) const {
    imageMetadata.write(ImageMetadataTokens::CPU, cpuinfo_get_package(0)->name);
}

void ImageMetadataCollector::collectRenderTimeIfPresent(ImageMetadata &imageMetadata) {
    if (renderTime) {
        imageMetadata.write(ImageMetadataTokens::RENDER_TIME, fmt::format("{:%T}", renderTime.value()));
        imageMetadata.write(ImageMetadataTokens::RENDER_TIME_SECONDS, renderTime.value());
    }
}

void ImageMetadataCollector::collectRenderSettingsIfPresent(ImageMetadata &imageMetadata) {
    if (scene == nullptr) {
        return;
    }

    imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_INTEGRATOR,
                        fmt::format("{}", scene->renderSettings.integratorType));
    imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_INTERSECTOR,
                        fmt::format("{}", scene->renderSettings.intersectorType));
    imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_MAX_SAMPLES, scene->renderSettings.maxSamples);
    imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_TILE_SEQUENCE_TYPE,
                        fmt::format("{}", scene->renderSettings.tileSequenceType));
    imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_TILE_SAMPLER_TYPE,
                        fmt::format("{}", scene->renderSettings.tileSamplerType));
    imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_ADAPTIVE_MAX_ERROR,
                        scene->renderSettings.adaptiveMaxError);
    imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_SAMPLES_PER_ADAPTIVE_PASS,
                        scene->renderSettings.samplesPerAdaptivePass);
    imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_USE_SPECTRAL_LENSING,
                        scene->renderSettings.useSpectralLensing ? 1 : 0);
    imageMetadata.write(
        ImageMetadataTokens::RENDER_SETTINGS_REGION_TO_RENDER,
        scene->renderSettings.regionToRender.has_value() ? scene->renderSettings.regionToRender->toString() : "none");
    collectIntegratorSettings(imageMetadata);
}

void ImageMetadataCollector::collectIntegratorSettings(ImageMetadata &imageMetadata) {
    if (scene == nullptr) {
        return;
    }
    for (const auto &entry : scene->renderSettings.integratorSettings.settings) {
        return std::visit(
            [&imageMetadata, &entry](auto &integratorSettingsValue) {
                imageMetadata.write("crayg/renderSettings/integratorSettings/" + entry.first, integratorSettingsValue);
            },
            entry.second);
    }
}

void ImageMetadataCollector::collectCamera(ImageMetadata &imageMetadata) {
    if (scene == nullptr) {
        return;
    }
    if (scene->camera == nullptr) {
        return;
    }

    const bool isRealisticCamera = scene->camera->getCameraType() == CameraType::REALISTIC;

    imageMetadata.write(ImageMetadataTokens::CAMERA_NAME, scene->camera->getName());
    imageMetadata.write(ImageMetadataTokens::CAMERA_FOCAL_LENGTH, scene->camera->getFocalLength());
    imageMetadata.write(ImageMetadataTokens::CAMERA_FILM_BACK_SIZE, scene->camera->getFilmbackSize());
    imageMetadata.write(ImageMetadataTokens::CAMERA_FOCUS_DISTANCE, scene->camera->getFocusDistance());
    imageMetadata.write(ImageMetadataTokens::CAMERA_F_STOP, scene->camera->getFStop());
    imageMetadata.write(ImageMetadataTokens::CAMERA_CAMERA_TYPE, fmt::format("{}", scene->camera->getCameraType()));
    if (isRealisticCamera) {
        auto &lens = scene->camera->getLens();
        imageMetadata.write(ImageMetadataTokens::CAMERA_LENS_NAME, fmt::format("{}", lens.metadata.name));
        imageMetadata.write(ImageMetadataTokens::CAMERA_LENS_SURFACE_COUNT, static_cast<int>(lens.surfaces.size()));
        imageMetadata.write(ImageMetadataTokens::CAMERA_LENS_EFFECTIVE_FOCAL_LENGTH, lens.metadata.focalLength * 10);
        imageMetadata.write(ImageMetadataTokens::CAMERA_LENS_MAXIMUM_F_NUMBER, lens.metadata.maximumAperture);
        imageMetadata.write(ImageMetadataTokens::CAMERA_LENS_IS_ANAMORPHIC, lens.metadata.isAnamorphic ? 1 : 0);
        imageMetadata.write(ImageMetadataTokens::CAMERA_LENS_SQUEEZE, lens.metadata.squeeze);
        imageMetadata.write(ImageMetadataTokens::CAMERA_LENS_CLOSEST_FOCAL_DISTANCE,
                            lens.metadata.closestFocalDistance);
        imageMetadata.write(ImageMetadataTokens::CAMERA_LENS_PATENT, lens.metadata.patent);
        imageMetadata.write(ImageMetadataTokens::CAMERA_LENS_DESCRIPTION, lens.metadata.description);
    }
}

void ImageMetadataCollector::collectSceneStats(ImageMetadata &imageMetadata) {
    if (scene == nullptr) {
        return;
    }

    imageMetadata.write(ImageMetadataTokens::SCENE_STATS_OBJECT_COUNT, static_cast<int>(scene->objects.size()));
    imageMetadata.write(ImageMetadataTokens::SCENE_STATS_PRIMITIVE_COUNT, static_cast<int>(scene->primitiveCount()));
}

}