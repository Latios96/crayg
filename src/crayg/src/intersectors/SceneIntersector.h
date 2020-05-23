//
// Created by Jan Honsbrok on 01.11.18.
//

#ifndef CRAYG_SCENEINTERSECTOR_H
#define CRAYG_SCENEINTERSECTOR_H

#include <scene/Scene.h>
#include <basics/Ray.h>

struct Intersection {
 public:
    Intersection(const Ray &ray, Vector3f location, SceneObject *object)
        : ray(ray), location(location), object(object) {}

    Ray ray;
    Vector3f location;
    SceneObject *object;

    bool isValid();
};

class SceneIntersector {
 public:
    explicit SceneIntersector(Scene &scene);

    virtual Imageable::Intersection intersect(Ray ray);
    bool isIntersecting(Ray ray);

    virtual ~SceneIntersector();

 private:
    Scene &scene;
};

#endif //CRAYG_SCENEINTERSECTOR_H
