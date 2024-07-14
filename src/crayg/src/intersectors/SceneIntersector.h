#pragma once

#include "scene/primitives/Sphere.h"
#include "scene/primitives/trianglemesh/Triangle.h"
#include <basics/Ray.h>
#include <scene/Scene.h>

namespace crayg {

struct HitStorage {

    Sphere sphere;
    Triangle triangle;

    HitStorage() {
    }

    virtual ~HitStorage() {
    }
};

class SceneIntersector {
  public:
    explicit SceneIntersector(Scene &scene) : scene(scene){};

    virtual Imageable::Intersection intersect(const Ray &ray, HitStorage &hitStorage) const = 0;
    virtual bool isOccluded(const Ray &ray, HitStorage &hitStorage, float maxDistance) const = 0;

    virtual ~SceneIntersector() = default;

  protected:
    Scene &scene;
};

}
