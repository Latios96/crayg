#include "Renderer.h"
#include "GeometryCompiler.h"
#include "Logger.h"
#include "SampleAccumulator.h"
#include "basics/MathUtils.h"
#include "image/ImageAlgorithms.h"
#include "integrators/IntegratorFactory.h"
#include "integrators/RaytracingIntegrator.h"
#include "intersectors/IntersectorFactory.h"
#include "sampling/Random.h"
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

    std::vector<ImageBucket> bucketSequence =
        ImageBucketSequences::getSequence(scene.renderSettings.resolution, 8, scene.renderSettings.bucketSequenceType);
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

bool shouldTerminate(int samplesTaken, int maxSamples, float error, float maxError) {
    if (samplesTaken > maxSamples) {
        return true;
    }
    if (error < maxError) {
        return true;
    }
    return false;
}

float perPixelError(const Color &fullySampled, const Color &halfSampled) {
    if (fullySampled ==
        Color::createBlack()) { // todo inf, nan oder sonst was sollte 0 ergeben, aber mal checken ob das so gut geht..
        return 0;
    }
    return (std::abs(fullySampled.r - halfSampled.r) + std::abs(fullySampled.g - halfSampled.g) +
            std::abs(fullySampled.b - halfSampled.b)) /
           std::sqrt(fullySampled.r + fullySampled.g + fullySampled.b); // todo tests
}

void Renderer::renderBucket(const ImageBucket &imageBucket) {
    BucketImageBuffer bucketImageBuffer(imageBucket);
    bucketImageBuffer.image.addChannelsFromSpec(requiredImageSpec({imageBucket.getWidth(), imageBucket.getHeight()}));
    outputDriver.prepareBucket(bucketImageBuffer.imageBucket);
    // todo add switch to switch between adaptive / not adaptive
    auto halfSampledBuffer = PixelBuffer::createRgbFloat({imageBucket.getWidth(), imageBucket.getHeight()});

    const int samplesPerPass = 8; // todo make these configurable
    const int maxSamples = std::pow(64, 2);
    const float maxError = 0.007;

    int samplesTaken = 0;
    float error = 150;
    while (!shouldTerminate(samplesTaken, maxSamples, error, maxError)) {
        error = 0;
        for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
            Color fullySampled = Color::createBlack();
            Color halfSampled = Color::createBlack();
            const auto samplePos = imageBucket.getPosition() + pixel;
            for (int i = 0; i < samplesPerPass; i++) {
                const Color &sampleColor =
                    renderSample(samplePos.x + Random::random(),
                                 samplePos.y + Random::random()); // todo: should be possible to add float + int Vec2
                fullySampled = fullySampled + sampleColor;
                if (i % 2 == 0) {
                    halfSampled = halfSampled + sampleColor;
                }
            }
            fullySampled = bucketImageBuffer.image.getValue(pixel) + fullySampled;
            bucketImageBuffer.image.setValue(pixel, fullySampled);
            halfSampled = halfSampledBuffer->getValue(pixel) + halfSampled;
            halfSampledBuffer->setValue(pixel, halfSampled);
            error += perPixelError(fullySampled / samplesTaken, halfSampled / (samplesTaken / 2));
        }
        error = error / (imageBucket.getWidth() * imageBucket.getHeight());
        samplesTaken += samplesPerPass;
    }

    for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
        auto pixelColor = bucketImageBuffer.image.getValue(pixel);
        bucketImageBuffer.image.setValue(pixel, pixelColor / samplesTaken);
    }
    const Color start = Color::fromRGB(0, 12, 253);
    const Color end = Color::fromRGB(0, 252, 129); // todo extract to ColorMap
    const float relativeSampleCount = static_cast<float>(samplesTaken) / static_cast<float>(maxSamples);
    ImageAlgorithms::fill(*bucketImageBuffer.image.getChannel("sampleCount"), // todo create buffer with
                          MathUtils::lerp(relativeSampleCount, start, end));

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
    return ImageSpecBuilder(resolution).createRgbFloatChannel("sampleCount").finish();
}

}
