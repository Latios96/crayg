#include <memory>

//
// Created by Jan Honsbrok on 04.11.18.
//

#include <image/ImageIterators.h>
#include <image/ImageBucketSequences.h>
#include <lightSamplers/LightSamplerFactory.h>
#include <numeric>
#include "Renderer.h"
#include "PineHoleCameraModel.h"
#include "utils/ProgressReporter.h"
#include "Logger.h"
#include <tbb/parallel_for.h>
#include <image/BucketImageBuffer.h>

Renderer::Renderer(Scene &scene, OutputDriver &outputDriver)
    : scene(scene), outputDriver(outputDriver) {

}
// todo init should not be in renderScene
void Renderer::renderScene() {
    init();

    Logger::info("Starting rendering..");

    std::vector<ImageBucket> bucketSequence = ImageBucketSequences::lineByLine(scene.renderSettings.resolution, 60);
    ProgressReporter reporter = ProgressReporter::createLoggingProgressReporter(bucketSequence.size(),
                                                                                "Rendering done by {}%, estimated time remaining: {}s");

    bool serialRendering = false;
    if (serialRendering) {
        renderSerial(reporter, bucketSequence);
    } else {
        renderParallel(reporter, bucketSequence);
    }

    Logger::info("Rendering done.");
    reporter.finish();
}

void Renderer::renderParallel(ProgressReporter &reporter,
                              const std::vector<ImageBucket> &bucketSequence) {
    tbb::parallel_for(static_cast<std::size_t>(0),
                      bucketSequence.size(),
                      [this, &reporter, &bucketSequence](int i) {
                          ImageBucket imageBucket = bucketSequence[i];
                          renderBucket(imageBucket);
                          reporter.iterationDone();
                      });
}
void Renderer::renderBucket(const ImageBucket &imageBucket) {
    BucketImageBuffer bucketImageBuffer(imageBucket);
    outputDriver.prepareBucket(bucketImageBuffer.imageBucket);

    for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
        Color pixelColor =
            renderPixel(PixelPosition(imageBucket.getX() + pixel.x,
                                      imageBucket.getY() + pixel.y));
        bucketImageBuffer.image.setValue(pixel.x, pixel.y, pixelColor);
    }
    outputDriver.writeBucketImageBuffer(bucketImageBuffer);
}

void Renderer::renderSerial(ProgressReporter &reporter, const std::vector<ImageBucket> &bucketSequence) {
    for (auto &imageBucket: bucketSequence) {
        renderBucket(imageBucket);
        reporter.iterationDone();
    }
}

void Renderer::init() {
    cameraModel =
        std::shared_ptr<CameraModel>(new PineHoleCameraModel(*scene.camera,
                                                             scene.renderSettings.resolution.getWidth(),
                                                             scene.renderSettings.resolution.getHeight()));
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

Color Renderer::renderPixel(const PixelPosition &pixel) {
    std::vector<Color> sampleColors;
    float stepSize = 1.0f / static_cast<float>(scene.renderSettings.maxSamples);
    for (int i = 0; i < scene.renderSettings.maxSamples; i++) {
        for (int a = 0; a < scene.renderSettings.maxSamples; a++) {
            sampleColors.push_back(renderSample(pixel.x - 0.5f + stepSize * i, pixel.y - 0.5f + stepSize * a));
        }
    }

    Color pixelColor =
        std::accumulate(sampleColors.begin(), sampleColors.end(), Color::createBlack()) / sampleColors.size();
    return pixelColor;
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

        return shadedColor * shadow;
    }
    return Color::createBlack();
}


