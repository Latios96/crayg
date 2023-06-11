#ifndef CRAYG_RENDERER_H
#define CRAYG_RENDERER_H

#include "bucketsamplers/BucketSampler.h"
#include "integrators/AbstractIntegrator.h"
#include "scene/camera/PineHoleCameraModel.h"
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
    Renderer(Scene &scene, OutputDriver &outputDriver, TaskReporter &taskReporter);

    void renderScene();

  private:
    Scene &scene;
    OutputDriver &outputDriver;
    std::unique_ptr<CameraModel> cameraModel;
    std::shared_ptr<SceneIntersector> sceneIntersector;
    TaskReporter &taskReporter;

    void init();

    void renderSerial(BaseTaskReporter::TaskProgressController &taskProgressController,
                      const std::vector<ImageBucket> &bucketSequence);
    void renderParallel(BaseTaskReporter::TaskProgressController &taskProgressController,
                        const std::vector<ImageBucket> &bucketSequence);
    void renderBucket(const ImageBucket &imageBucket);
    Color renderSample(const Vector2f &samplePos);

    std::unique_ptr<AbstractIntegrator> integrator;
    std::unique_ptr<BucketSampler> bucketSampler;

    void writeImageMetadata(std::chrono::seconds renderTime);
    ImageSpec requiredImageSpec(const Resolution &resolution) const;
};

}

#endif // CRAYG_RENDERER_H
