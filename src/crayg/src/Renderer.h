//
// Created by Jan Honsbrok on 04.11.18.
//

#ifndef CRAYG_RENDERER_H
#define CRAYG_RENDERER_H

#include <scene/Scene.h>
#include <scene/Camera.h>
#include <image/Image.h>
#include <basics/Color.h>
#include "PineHoleCameraModel.h"
#include <intersectors/SceneIntersector.h>
#include <lightSamplers/LightSampler.h>
#include <utils/ProgressReporter.h>
#include <image/ImageOutputDriver.h>
#include <basics/Resolution.h>
#include <scene/RenderSettings.h>
#include "ShadingMethod.h"

class Renderer {
 public:
    Renderer(Scene &scene, OutputDriver &outputDriver);

    void renderScene();
 private:
    Scene &scene;
    OutputDriver &outputDriver;
    std::shared_ptr<CameraModel> cameraModel;
    std::shared_ptr<SceneIntersector> sceneIntersector;
    std::shared_ptr<ShadingMethod> lambertMethod;
    std::vector<std::shared_ptr<LightSampler>> lightSamplers;
    Color renderPixel(const PixelPosition &pixel);

    void init();
    Color renderSample(float x, float y);
    void renderSerial(ProgressReporter &reporter, const std::vector<ImageBucket> &bucketSequence);
    void renderParallel(ProgressReporter &reporter,
                        const std::vector<ImageBucket> &bucketSequence);
    void renderBucket(const ImageBucket &imageBucket);
};

#endif //CRAYG_RENDERER_H
