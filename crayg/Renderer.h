//
// Created by Jan Honsbrok on 04.11.18.
//

#ifndef CRAYG_RENDERER_H
#define CRAYG_RENDERER_H


#include <scene/Scene.h>
#include <scene/Camera.h>
#include <image/Image.h>
#include <foundation/Color.h>

class Renderer {
public:
    Renderer(Scene &scene, Image &image);

    void renderScene();
private:
    Scene& scene;
    Image& image;

    Color shadePoint(Vector3f point, SceneObject& object);
};


#endif //CRAYG_RENDERER_H
