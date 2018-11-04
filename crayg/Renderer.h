//
// Created by Jan Honsbrok on 04.11.18.
//

#ifndef CRAYG_RENDERER_H
#define CRAYG_RENDERER_H


#include <scene/Scene.h>
#include <scene/Camera.h>
#include <image/Image.h>

class Renderer {
public:
    Renderer(Scene &scene, Camera &camera, Image &image);

    void renderScene();
private:
    Scene& scene;
    Camera& camera;
    Image& image;
};


#endif //CRAYG_RENDERER_H
