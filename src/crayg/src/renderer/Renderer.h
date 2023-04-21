#ifndef CRAYG_RENDERER_H
#define CRAYG_RENDERER_H

#include "integrators/AbstractIntegrator.h"
#include "scene/camera/PineHoleCameraModel.h"
#include "scene/camera/lookup/LensRayLookupTable.h"
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
    Renderer(Scene &scene, OutputDriver &outputDriver);

    void renderScene();

  private:
    Scene &scene;
    OutputDriver &outputDriver;
    std::unique_ptr<CameraModel> cameraModel;
    std::shared_ptr<SceneIntersector> sceneIntersector;

    void init();

    void renderSerial(ProgressReporter &reporter, const std::vector<ImageBucket> &bucketSequence);
    void renderParallel(ProgressReporter &reporter, const std::vector<ImageBucket> &bucketSequence);
    void renderBucket(const ImageBucket &imageBucket);
    Color renderPixel(const Vector2i &pixel);
    Color renderSample(float x, float y);

    std::unique_ptr<AbstractIntegrator> integrator;
    void writeImageMetadata(std::chrono::seconds renderTime);
    ImageSpec requiredImageSpec(const Resolution &resolution) const;
    LensRayLookupTable lensRayLookupTable;
};

}

#endif // CRAYG_RENDERER_H
