#pragma once

#include "crayg/foundation/math/geometry/Ray.h"
#include "crayg/scene/Scene.h"
#include "crayg/scene/primitives/Sphere.h"
#include "crayg/scene/primitives/trianglemesh/Triangle.h"

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
