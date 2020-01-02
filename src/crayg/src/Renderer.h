//
// Created by Jan Honsbrok on 04.11.18.
//

#ifndef CRAYG_RENDERER_H
#define CRAYG_RENDERER_H

#include <scene/Scene.h>
#include <scene/Camera.h>
#include <image/Image.h>
#include <foundation/Color.h>
#include "PineHoleCameraModel.h"
#include <intersectors/SceneIntersector.h>
#include <lightSamplers/LightSampler.h>
#include <utils/ProgressReporter.h>
#include "ShadingMethod.h"

class Renderer {
 public:
    Renderer(Scene &scene, Image &image);

    void renderScene();
 private:
    Scene &scene;
    Image &image;
    std::shared_ptr<CameraModel> cameraModel;
    std::shared_ptr<SceneIntersector> sceneIntersector;
    std::shared_ptr<ShadingMethod> lambertMethod;
    std::vector<std::shared_ptr<LightSampler>> lightSamplers;
    void renderPixel(const PixelPosition &pixel);

    void init();
    Color renderSample(float x, float y);
    void renderSerial(ProgressReporter &reporter);
    void renderParallel(ProgressReporter &reporter);
};

#endif //CRAYG_RENDERER_H
