#pragma once

#include <basics/Ray.h>
#include <scene/Scene.h>

namespace crayg {

class SceneIntersector {
  public:
    explicit SceneIntersector(Scene &scene) : scene(scene){};

    virtual Imageable::Intersection intersect(const Ray &ray) const = 0;
    virtual bool isOccluded(const Ray &ray, float maxDistance) const = 0;

    virtual ~SceneIntersector() = default;

  protected:
    Scene &scene;
};

}
