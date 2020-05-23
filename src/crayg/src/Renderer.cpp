#include <memory>

//
// Created by Jan Honsbrok on 04.11.18.
//

#include <image/ImageIterators.h>
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

    bool serialRendering = false;
    if (serialRendering) {
        renderSerial(reporter);
    } else {
        renderParallel(reporter);
    }

    Logger::info("Rendering done.");
    reporter.finish();
}
void Renderer::renderParallel(ProgressReporter &reporter) {
    for(int x = 0; x < image.getWidth(); x++) {
        for (int y = 0; y < image.getHeight(); y++) {
            renderPixel(PixelPosition(x, y));
            reporter.iterationDone();
        }
    };
}
void Renderer::renderSerial(ProgressReporter &reporter) {
    for (auto pixel : ImageIterators::lineByLine(image)) {
        renderPixel(pixel);
        reporter.iterationDone();
    }
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
    std::vector<Color> sampleColors;
    int maxSampleCount = 2;
    float stepSize = 1.0f / maxSampleCount;
    for (int i = 0; i < maxSampleCount; i++) {
        for (int a = 0; a < maxSampleCount; a++) {
            sampleColors.push_back(renderSample(pixel.x - 0.5f + stepSize * i, pixel.y - 0.5f + stepSize * a));
        }
    }

    Color pixelColor =
        std::accumulate(sampleColors.begin(), sampleColors.end(), Color::createBlack()) / sampleColors.size();
    image.setValue(pixel.x, pixel.y, pixelColor);

}
Color Renderer::renderSample(float x, float y) {
    Ray ray = cameraModel->createPrimaryRay(x, y);
    auto intersection = sceneIntersector->intersect(ray);

    const bool hasHit = intersection.imageable != nullptr;
    if (hasHit) {
        Vector3f location = ray.startPoint + (ray.direction * intersection.rayParameter);
        Imageable &object = *intersection.imageable;
        Color shadedColor = lambertMethod->lambertShading(location, object);

        float shadow = 1.0;

        // NOTE: this is ugly, but only this way we can avoid cyclic includes between Light, Scene and SceneIntersector at the moment
        for (auto &lightSampler : lightSamplers) {
            shadow = lightSampler->calculateShadowFactor(location + (object.getNormal(location) * 0.001));
        }

        return shadedColor;// * shadow;
    }
    return Color::createBlack();
}

