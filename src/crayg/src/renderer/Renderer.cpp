#include "Renderer.h"
#include "BucketSizeEstimator.h"
#include "GeometryCompiler.h"
#include "Logger.h"
#include "SampleAccumulator.h"
#include "integrators/IntegratorFactory.h"
#include "integrators/RaytracingIntegrator.h"
#include "intersectors/IntersectorFactory.h"
#include "scene/camera/CameraModelFactory.h"
#include "utils/ImageMetadataCollector.h"
#include "utils/ProgressReporter.h"
#include "utils/StopWatch.h"
#include <image/BucketImageBuffer.h>
#include <image/imageiterators/buckets/ImageBucketSequences.h>
#include <image/imageiterators/pixels/ImageIterators.h>
#include <memory>
#include <numeric>
#include <tbb/concurrent_queue.h>
#include <tbb/task_group.h>

namespace crayg {

Renderer::Renderer(Scene &scene, OutputDriver &outputDriver) : scene(scene), outputDriver(outputDriver) {
}

void Renderer::renderScene() {
    init();
    Logger::info("Starting rendering..");

    outputDriver.initialize(requiredImageSpec(scene.renderSettings.resolution));

    std::vector<ImageBucket> bucketSequence = ImageBucketSequences::lineByLine(scene.renderSettings.resolution, 8);
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
    tbb::concurrent_queue<ImageBucket> bucketQueue(bucketSequence.begin(), bucketSequence.end());
    tbb::task_group task_group;

    for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
        task_group.run([&bucketQueue, &reporter, this]() {
            ImageBucket imageBucket;
            while (bucketQueue.try_pop(imageBucket)) {
                renderBucket(imageBucket);
                reporter.iterationDone();
            }
        });
    }
    task_group.wait();
}

void Renderer::renderBucket(const ImageBucket &imageBucket) {
    BucketImageBuffer bucketImageBuffer(imageBucket);
    bucketImageBuffer.image.addChannelsFromSpec(requiredImageSpec({imageBucket.getWidth(), imageBucket.getHeight()}));
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
    Logger::info("Objects in scene: {:L}", scene.objects.size());
    Logger::info("Primitives in scene: {:L}", scene.primitiveCount());

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
    ImageMetadataCollector imageMetadataCollector(renderTime, &scene);

    ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

    outputDriver.writeImageMetadata(imageMetadata);
}

ImageSpec Renderer::requiredImageSpec(const Resolution &resolution) const {
    return ImageSpecBuilder(resolution).finish();
}

}
