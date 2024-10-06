#include "Renderer.h"
#include "GeometryCompiler.h"
#include "Logger.h"
#include "SampleAccumulator.h"
#include "image/ImageAlgorithms.h"
#include "image/imageiterators/buckets/bucketqueues/BucketQueue.h"
#include "integrators/IntegratorFactory.h"
#include "integrators/RaytracingIntegrator.h"
#include "intersectors/IntersectorFactory.h"
#include "renderer/bucketsamplers/BucketSamplerFactory.h"
#include "sampling/Random.h"
#include "scene/camera/CameraModelFactory.h"
#include "scene/camera/realistic/Wavelengths.h"
#include "utils/ImageMetadataCollector.h"
#include "utils/ProgressReporter.h"
#include "utils/StopWatch.h"
#include "utils/TaskReporter.h"
#include "utils/tracing/CraygTracing.h"
#include <Imath/half.h>
#include <image/BucketImageBuffer.h>
#include <image/imageiterators/buckets/ImageBucketSequences.h>
#include <memory>
#include <numeric>
#include <tbb/task_group.h>
#include <variant>

namespace crayg {

Renderer::Renderer(Scene &scene, OutputDriver &outputDriver, BaseTaskReporter &taskReporter, BucketQueue &bucketQueue)
    : scene(scene), outputDriver(outputDriver), taskReporter(taskReporter), bucketQueue(bucketQueue) {
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
    bucketStats.processBucketTimes(outputDriver, scene.renderSettings.resolution);
}

void Renderer::renderParallel(BaseTaskReporter::TaskProgressController &taskProgressController) {
    CRG_TRACE_SCOPE("Renderer");
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
    CRG_TRACE_SCOPE("Renderer");
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

void Renderer::renderBucket(const ImageBucket &imageBucket) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    BucketImageBuffer bucketImageBuffer(imageBucket);
    bucketImageBuffer.image.addChannelsFromSpec(requiredImageSpec({imageBucket.getWidth(), imageBucket.getHeight()}));
    outputDriver.prepareBucket(bucketImageBuffer.imageBucket);

    bucketSampler->sampleBucket(bucketImageBuffer);

    bucketStats.processBucketTime(bucketImageBuffer, startTime);

    outputDriver.writeBucketImageBuffer(bucketImageBuffer);
}

void Renderer::init() {
    CRG_TRACE_SCOPE("Renderer");
    bucketSampler = BucketSamplerFactory::createBucketSampler(
        scene.renderSettings, [this](Vector2f samplePos) { return renderSample(samplePos); });
    {
        InformativeScopedStopWatch initializeCamera("Initialize camera");
        cameraModel = CameraModelFactory::createCameraModel(*scene.camera, scene.renderSettings.resolution);
        cameraModel->init(taskReporter);
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
    auto rayWithWeight = cameraModel->createPrimaryRay(samplePos, waveLength);
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
    bucketSampler->addRequiredImageSpecs(builder);
    builder.createGreyFloatChannel("absoluteRenderTime");
    builder.createRgbFloatChannel("relativeRenderTime");
    return builder.finish();
}

}
