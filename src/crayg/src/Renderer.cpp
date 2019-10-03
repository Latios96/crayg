#include <memory>

//
// Created by Jan Honsbrok on 04.11.18.
//

#include <image/ImageIterators.h>
#include <spdlog/spdlog.h>
#include <lightSamplers/LightSamplerFactory.h>
#include <numeric>
#include "Renderer.h"
#include "PineHoleCameraModel.h"
#include "utils/ProgressReporter.h"
#include "Logger.h"

Renderer::Renderer(Scene &scene, Image &image) : scene(scene), image(image) {}

// todo init should not be in renderScene
void Renderer::renderScene() {
    init();

    Logger::info("Starting rendering..");

    int pixelCount = image.getHeight() * image.getWidth();
    ProgressReporter reporter = ProgressReporter::createLoggingProgressReporter(pixelCount,
                                                                                "Rendering done by {}%, estimated time remaining: {}s");

    for (auto pixel : ImageIterators::lineByLine(image)) {
        renderPixel(pixel);
        reporter.iterationDone();
    }
    Logger::info("Rendering done.");
    reporter.finish();
}

void Renderer::init() {
    cameraModel =
        std::shared_ptr<CameraModel>(new PineHoleCameraModel(*scene.camera, image.getWidth(), image.getHeight()));
    lambertMethod = std::make_shared<ShadingMethod>(scene);

    Logger::info("Execute Imageable::beforeRender...");
    for (auto &imageable : scene.objects) {
        imageable->beforeRender();
    }

    Logger::info("Creating SceneIntersector...");
    sceneIntersector = std::make_shared<SceneIntersector>(scene);

    Logger::info("Creating LightSamplers...");
    for (auto &light : scene.lights) {
        lightSamplers.push_back(LightSamplerFactory::createLightSampler(*light, *sceneIntersector));
    }
}

void Renderer::renderPixel(const PixelPosition &pixel) {
    Ray ray = cameraModel->createPrimaryRay(pixel.x, pixel.y);

    auto intersection = sceneIntersector->intersect(ray);

    const bool hasHit = intersection.imageable != nullptr;
    if (hasHit) {
        Vector3f location = ray.startPoint + (ray.direction * intersection.rayParameter);
        Imageable &object = *intersection.imageable;
        Color shadedColor = lambertMethod->lambertShading(location, object);

        float shadow = 1.0;
        for (auto &lightSampler : lightSamplers) {
            shadow = lightSampler->calculateShadowFactor(location + (object.getNormal(location) * 0.001));
        }

        //image.setValue(pixel.x, pixel.y, Color::createGrey(shadow));
        image.setValue(pixel.x, pixel.y, shadedColor * shadow);
    }
}

