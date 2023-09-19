#include "Renderer.h"
#include "GeometryCompiler.h"
#include "Logger.h"
#include "SampleAccumulator.h"
#include "image/imageiterators/buckets/bucketqueues/BucketQueue.h"
#include "image/imageiterators/pixels/ImageIterators.h"
#include "integrators/IntegratorFactory.h"
#include "integrators/RaytracingIntegrator.h"
#include "intersectors/IntersectorFactory.h"
#include "sampling/Random.h"
#include "scene/camera/CameraModelFactory.h"
#include "scene/camera/realistic/Wavelengths.h"
#include "utils/ImageMetadataCollector.h"
#include "utils/ProgressReporter.h"
#include "utils/StopWatch.h"
#include "utils/TaskReporter.h"
#include <image/BucketImageBuffer.h>
#include <image/imageiterators/buckets/ImageBucketSequences.h>
#include <memory>
#include <numeric>
#include <tbb/task_group.h>

namespace crayg {

Renderer::Renderer(Scene &scene, OutputDriver &outputDriver, BaseTaskReporter &taskReporter, BucketQueue &bucketQueue)
    : scene(scene), outputDriver(outputDriver), taskReporter(taskReporter), bucketQueue(bucketQueue),
      lensRayLookupTable(scene.renderSettings.resolution,
                         scene.renderSettings.maxSamples * scene.renderSettings.maxSamples) {
}

void Renderer::renderScene() {
    init();
    Logger::info("Starting rendering..");

    outputDriver.initialize(requiredImageSpec(scene.renderSettings.resolution));

    bucketSequence =
        ImageBucketSequences::getSequence(scene.renderSettings.resolution, 8, scene.renderSettings.bucketSequenceType);
    auto taskProgressController = taskReporter.startTask("Rendering", bucketSequence.size());

    bool serialRendering = false;
    if (serialRendering) {
        renderSerial(taskProgressController);
    } else {
        renderParallel(taskProgressController);
    }

    Logger::info("Rendering done.");
    const auto renderTime = taskProgressController.finish();
    writeImageMetadata(renderTime);
}

void Renderer::renderParallel(BaseTaskReporter::TaskProgressController &taskProgressController) {
    bucketQueue.start(bucketSequence);
    tbb::task_group task_group;

    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++) {
        task_group.run([&taskProgressController, this]() {
            while (true) {
                const auto imageBucket = bucketQueue.nextBucket();
                if (!imageBucket) {
                    return;
                }
                renderBucket(*imageBucket);
                taskProgressController.iterationDone();
            }
        });
    }
    task_group.wait();
}

void Renderer::renderSerial(BaseTaskReporter::TaskProgressController &taskProgressController) {
    bucketQueue.start(bucketSequence);
    while (true) {
        const auto imageBucket = bucketQueue.nextBucket();
        if (!imageBucket) {
            return;
        }
        renderBucket(*imageBucket);
        taskProgressController.iterationDone();
    }
}

Color Renderer::renderPixel(const Vector2i &pixel) {
    SampleAccumulator sampleAccumulator;

    if (scene.camera->getCameraType() == CameraType::RAY_LUT) {
        const int samples = std::pow(scene.renderSettings.maxSamples, 2);
        for (int i = 0; i < samples; i++) {
            auto ray = lensRayLookupTable.getRay(pixel, i);
            if (ray == Ray({0, 0, 0}, {0, 0, 0})) {
                sampleAccumulator.addSample(Color::createBlack());
                continue;
            }
            sampleAccumulator.addSample(integrator->integrate(ray, 0));
        }
    } else {
        for (int i = 0; i < scene.renderSettings.maxSamples; i++) {
            for (int a = 0; a < scene.renderSettings.maxSamples; a++) {
                sampleAccumulator.addSample(renderSample(Random::randomVector2f() + pixel));
            }
        }
    }

    return sampleAccumulator.getValue();
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

void Renderer::init() {
    {
        InformativeScopedStopWatch buildBvh(fmt::format("Initialize camera of type {}", scene.camera->getCameraType()));
        cameraModel = CameraModelFactory::createCameraModel(*scene.camera, scene.renderSettings.resolution);
        cameraModel->init(taskReporter);
    }
    if (scene.camera->getCameraType() == CameraType::RAY_LUT) {
        lensRayLookupTable.generate(*cameraModel);
    }

    GeometryCompiler geometryCompiler(scene, taskReporter);
    geometryCompiler.compile();
    Logger::info("Objects in scene: {:L}", scene.objects.size());
    Logger::info("Primitives in scene: {:L}", scene.primitiveCount());

    auto progressController = taskReporter.startTask("Building SceneIntersector", 1);
    sceneIntersector = IntersectorFactory::createSceneIntersector(scene.renderSettings.intersectorType, scene);
    integrator = std::unique_ptr<AbstractIntegrator>(IntegratorFactory::createIntegrator(
        scene.renderSettings.integratorType, scene, sceneIntersector, scene.renderSettings.integratorSettings));
    progressController.finish();
}

Color Renderer::renderSample(const Vector2f &samplePos) {
    if (scene.renderSettings.useSpectralLensing) {
        const float r = renderSample(samplePos, WavelengthsRgb::R).r;
        const float g = renderSample(samplePos, WavelengthsRgb::G).g;
        const float b = renderSample(samplePos, WavelengthsRgb::B).b;
        return {r, g, b};
    }
    return renderSample(samplePos, FraunhoferLines::SODIUM.wavelength);
}

Color Renderer::renderSample(const Vector2f &samplePos, float waveLength) {
    auto rayWithWeight = cameraModel->createPrimaryRay(samplePos.x, samplePos.y, waveLength);
    if (!rayWithWeight.ray) {
        return Color::createBlack();
    }
    return integrator->integrate(*rayWithWeight.ray, 0) * rayWithWeight.weight;
}

void Renderer::writeImageMetadata(std::chrono::seconds renderTime) {
    ImageMetadataCollector imageMetadataCollector(renderTime, &scene);

    ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

    outputDriver.writeImageMetadata(imageMetadata);
}

ImageSpec Renderer::requiredImageSpec(const Resolution &resolution) const {
    ImageSpecBuilder builder(resolution);
    return builder.finish();
}
}
