#include "Renderer.h"
#include "GeometryCompiler.h"
#include "Logger.h"
#include "SampleAccumulator.h"
#include "integrators/IntegratorFactory.h"
#include "integrators/RaytracingIntegrator.h"
#include "intersectors/IntersectorFactory.h"
#include "renderer/bucketsamplers/BucketSamplerFactory.h"
#include "sampling/Random.h"
#include "scene/camera/CameraModelFactory.h"
#include "utils/ImageMetadataCollector.h"
#include "utils/ProgressReporter.h"
#include "utils/StopWatch.h"
#include "utils/TaskReporter.h"
#include <image/BucketImageBuffer.h>
#include <image/imageiterators/buckets/ImageBucketSequences.h>
#include <memory>
#include <numeric>
#include <tbb/concurrent_queue.h>
#include <tbb/task_group.h>

namespace crayg {

Renderer::Renderer(Scene &scene, OutputDriver &outputDriver, TaskReporter &taskReporter)
    : scene(scene), outputDriver(outputDriver), taskReporter(taskReporter) {
}

void Renderer::renderScene() {
    init();
    Logger::info("Starting rendering..");

    outputDriver.initialize(requiredImageSpec(scene.renderSettings.resolution));

    std::vector<ImageBucket> bucketSequence =
        ImageBucketSequences::getSequence(scene.renderSettings.resolution, 8, scene.renderSettings.bucketSequenceType);
    auto taskProgressController = taskReporter.startTask("Rendering", bucketSequence.size());

    bool serialRendering = false;
    if (serialRendering) {
        renderSerial(taskProgressController, bucketSequence);
    } else {
        renderParallel(taskProgressController, bucketSequence);
    }

    Logger::info("Rendering done.");
    const auto renderTime = taskProgressController.finish();
    writeImageMetadata(renderTime);
}

void Renderer::renderParallel(BaseTaskReporter::TaskProgressController &taskProgressController,
                              const std::vector<ImageBucket> &bucketSequence) {
    tbb::concurrent_queue<ImageBucket> bucketQueue(bucketSequence.begin(), bucketSequence.end());
    tbb::task_group task_group;

    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++) {
        task_group.run([&bucketQueue, &taskProgressController, this]() {
            ImageBucket imageBucket;
            while (bucketQueue.try_pop(imageBucket)) {
                renderBucket(imageBucket);
                taskProgressController.iterationDone();
            }
        });
    }
    task_group.wait();
}

void Renderer::renderSerial(BaseTaskReporter::TaskProgressController &taskProgressController,
                            const std::vector<ImageBucket> &bucketSequence) {
    for (auto &imageBucket : bucketSequence) {
        renderBucket(imageBucket);
        taskProgressController.iterationDone();
    }
}

void Renderer::renderBucket(const ImageBucket &imageBucket) {
    BucketImageBuffer bucketImageBuffer(imageBucket);
    bucketImageBuffer.image.addChannelsFromSpec(requiredImageSpec({imageBucket.getWidth(), imageBucket.getHeight()}));
    outputDriver.prepareBucket(bucketImageBuffer.imageBucket);

    bucketSampler->sampleBucket(bucketImageBuffer);

    outputDriver.writeBucketImageBuffer(bucketImageBuffer);
}

void Renderer::init() {
    bucketSampler = BucketSamplerFactory::createBucketSampler(
        scene.renderSettings, [this](Vector2f samplePos) { return renderSample(samplePos); });
    {
        InformativeScopedStopWatch buildBvh("Initialize camera");
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
    auto ray = cameraModel->createPrimaryRay(samplePos.x, samplePos.y);
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
    ImageSpecBuilder builder(resolution);
    bucketSampler->addRequiredImageSpecs(builder);
    return builder.finish();
}

}
