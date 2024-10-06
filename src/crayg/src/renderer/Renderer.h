#pragma once

#include "BucketStats.h"
#include "bucketsamplers/BucketSampler.h"
#include "image/imageiterators/buckets/bucketqueues/BucketQueue.h"
#include "integrators/AbstractIntegrator.h"
#include "scene/camera/pinehole/PineHoleCameraModel.h"
#include "utils/TaskReporter.h"
#include <basics/Color.h>
#include <basics/Resolution.h>
#include <image/Image.h>
#include <intersectors/SceneIntersector.h>
#include <outputdrivers/ImageOutputDriver.h>
#include <scene/RenderSettings.h>
#include <scene/Scene.h>
#include <scene/camera/Camera.h>
#include <utils/ProgressReporter.h>

namespace crayg {

class Renderer {
  public:
    Renderer(Scene &scene, OutputDriver &outputDriver, BaseTaskReporter &taskReporter, BucketQueue &bucketQueue);

    void renderScene();

  private:
    Scene &scene;
    OutputDriver &outputDriver;
    std::unique_ptr<CameraModel> cameraModel;
    std::shared_ptr<SceneIntersector> sceneIntersector;
    BaseTaskReporter &taskReporter;
    BucketQueue &bucketQueue;
    std::vector<ImageBucket> bucketSequence;

    BucketStats bucketStats;

    void init();
    void initBuckets();

    void renderSerial(BaseTaskReporter::TaskProgressController &taskProgressController);
    void renderParallel(BaseTaskReporter::TaskProgressController &taskProgressController);
    void renderBucket(const ImageBucket &imageBucket);
    Color renderSample(const Vector2f &samplePos);
    Color renderSample(const Vector2f &samplePos, float waveLength);

    std::unique_ptr<AbstractIntegrator> integrator;
    std::unique_ptr<BucketSampler> bucketSampler;

    void writeImageMetadata(std::chrono::seconds renderTime);
    ImageSpec requiredImageSpec(const Resolution &resolution) const;
};

}
