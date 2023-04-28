#ifndef CRAYG_SCENEINTERSECTOR_H
#define CRAYG_SCENEINTERSECTOR_H

#include <basics/Ray.h>
#include <scene/Scene.h>

namespace crayg {

class SceneIntersector {
  public:
    explicit SceneIntersector(Scene &scene);

    virtual Imageable::Intersection intersect(const Ray &ray) const;
    virtual bool isIntersecting(const Ray &ray, float maxDistance) const;

    virtual ~SceneIntersector();

  protected:
    Scene &scene;
};

}

#endif // CRAYG_SCENEINTERSECTOR_H
