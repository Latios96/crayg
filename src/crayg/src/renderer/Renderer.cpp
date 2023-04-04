#include "Renderer.h"
#include "BucketSizeEstimator.h"
#include "GeometryCompiler.h"
#include "Logger.h"
#include "SampleAccumulator.h"
#include "integrators/IntegratorFactory.h"
#include "integrators/RaytracingIntegrator.h"
#include "intersectors/IntersectorFactory.h"
#include "scene/camera/CameraModelFactory.h"
#include "scene/camera/PineHoleCameraModel.h"
#include "utils/ImageMetadataCollector.h"
#include "utils/ProgressReporter.h"
#include "utils/StopWatch.h"
#include <image/BucketImageBuffer.h>
#include <image/ImageBucketSequences.h>
#include <image/ImageIterators.h>
#include <memory>
#include <numeric>
#include <tbb/parallel_for.h>

namespace crayg {

Renderer::Renderer(Scene &scene, OutputDriver &outputDriver) : scene(scene), outputDriver(outputDriver) {
}

void Renderer::renderScene() {
    init();
    Logger::info("Starting rendering..");

    outputDriver.initialize(requiredImageSpec());

    const BucketSizeEstimator bucketSizeEstimator(scene.renderSettings);
    const int bucketSize = bucketSizeEstimator.estimateBucketSize();

    std::vector<ImageBucket> bucketSequence =
        ImageBucketSequences::lineByLine(scene.renderSettings.resolution, bucketSize);
    ProgressReporter reporter =
        ProgressReporter::createLoggingProgressReporter(static_cast<int>(bucketSequence.size()), "Rendering");

    bool serialRendering = false;
    if (serialRendering) {
        renderSerial(reporter, bucketSequence);
    } else {
        renderParallel(reporter, bucketSequence);
    }

    Logger::info("Rendering done.");
    const auto renderTime = reporter.finish();
    writeImageMetadata(renderTime);
}

void Renderer::renderParallel(ProgressReporter &reporter, const std::vector<ImageBucket> &bucketSequence) {
    tbb::parallel_for(static_cast<std::size_t>(0), bucketSequence.size(), [this, &reporter, &bucketSequence](int i) {
        ImageBucket imageBucket = bucketSequence[i];
        renderBucket(imageBucket);
        reporter.iterationDone();
    });
}

void Renderer::renderBucket(const ImageBucket &imageBucket) {
    BucketImageBuffer bucketImageBuffer(imageBucket);
    outputDriver.prepareBucket(bucketImageBuffer.imageBucket);

    for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
        Color pixelColor = renderPixel(pixel + imageBucket.getPosition());
        bucketImageBuffer.image.setValue(pixel, pixelColor);
    }
    outputDriver.writeBucketImageBuffer(bucketImageBuffer);
}

void Renderer::renderSerial(ProgressReporter &reporter, const std::vector<ImageBucket> &bucketSequence) {
    for (auto &imageBucket : bucketSequence) {
        renderBucket(imageBucket);
        reporter.iterationDone();
    }
}

void Renderer::init() {
    {
        InformativeScopedStopWatch buildBvh("Initialize camera");
        cameraModel = CameraModelFactory::createCameraModel(*scene.camera, scene.renderSettings.resolution);
        cameraModel->init();
    }

    GeometryCompiler geometryCompiler(scene);
    geometryCompiler.compile();

    {
        InformativeScopedStopWatch buildBvh("Building SceneIntersector");
        sceneIntersector = IntersectorFactory::createSceneIntersector(scene.renderSettings.intersectorType, scene);
        integrator = std::unique_ptr<AbstractIntegrator>(IntegratorFactory::createIntegrator(
            scene.renderSettings.integratorType, scene, sceneIntersector, scene.renderSettings.integratorSettings));
    }
}

Color Renderer::renderPixel(const Vector2i &pixel) {
    SampleAccumulator sampleAccumulator;

    float stepSize = 1.0f / static_cast<float>(scene.renderSettings.maxSamples);
    for (int i = 0; i < scene.renderSettings.maxSamples; i++) {
        for (int a = 0; a < scene.renderSettings.maxSamples; a++) {
            sampleAccumulator.addSample(renderSample(pixel.x + stepSize * i, pixel.y + stepSize * a));
        }
    }

    return sampleAccumulator.getValue();
}

Color Renderer::renderSample(float x, float y) {
    auto ray = cameraModel->createPrimaryRay(x, y);
    if (!ray) {
        return Color::createBlack();
    }
    return integrator->integrate(*ray, 0);
}

void Renderer::writeImageMetadata(std::chrono::seconds renderTime) {
    ImageMetadataCollector imageMetadataCollector(renderTime, scene.renderSettings);

    ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

    outputDriver.writeImageMetadata(imageMetadata);
}

ImageSpec Renderer::requiredImageSpec() const {
    return ImageSpecBuilder(scene.renderSettings.resolution).finish();
}

}
