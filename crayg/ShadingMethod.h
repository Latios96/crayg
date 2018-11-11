//
// Created by Jan Honsbrok on 11.11.18.
//

#ifndef CRAYG_SHADINGMETHODS_H
#define CRAYG_SHADINGMETHODS_H


#include <foundation/Color.h>
#include <foundation/Vector3f.h>
#include <scene/SceneObject.h>
#include <scene/Scene.h>

class ShadingMethod {
public:
    ShadingMethod(Scene &scene);

    Color lambertShading(Vector3f point, SceneObject& object);
    Color colorForLight(const Vector3f &point, const Vector3f &normal, const std::shared_ptr<Light> &light) const;
private:
    Scene &scene;

};


// todo refractor into own class
// todo add tests


#endif //CRAYG_SHADINGMETHODS_H
