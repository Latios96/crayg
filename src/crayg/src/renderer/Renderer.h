#ifndef CRAYG_RENDERER_H
#define CRAYG_RENDERER_H

#include <scene/Scene.h>
#include <scene/Camera.h>
#include <image/Image.h>
#include <basics/Color.h>
#include "PineHoleCameraModel.h"
#include <intersectors/SceneIntersector.h>
#include <utils/ProgressReporter.h>
#include <image/ImageOutputDriver.h>
#include <basics/Resolution.h>
#include <scene/RenderSettings.h>
#include "integrators/AbstractIntegrator.h"

namespace crayg {

class Renderer {
 public:
    Renderer(Scene &scene, OutputDriver &outputDriver);

    void renderScene();
 private:
    Scene &scene;
    OutputDriver &outputDriver;
    std::shared_ptr<CameraModel> cameraModel;
    std::shared_ptr<SceneIntersector> sceneIntersector;

    void init();

    void renderSerial(ProgressReporter &reporter, const std::vector<ImageBucket> &bucketSequence);
    void renderParallel(ProgressReporter &reporter,
                        const std::vector<ImageBucket> &bucketSequence);
    void renderBucket(const ImageBucket &imageBucket);
    Color renderPixel(const PixelPosition &pixel);
    Color renderSample(float x, float y);

    std::unique_ptr<AbstractIntegrator> integrator;
};

}

#endif //CRAYG_RENDERER_H
