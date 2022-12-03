#ifndef CRAYG_SCENEINTERSECTOR_H
#define CRAYG_SCENEINTERSECTOR_H

#include <scene/Scene.h>
#include <basics/Ray.h>

namespace crayg {



class SceneIntersector {
 public:
    explicit SceneIntersector(Scene &scene);

    virtual Imageable::Intersection intersect(const Ray &ray) const;
    virtual bool isIntersecting(const Ray &ray) const;

    virtual ~SceneIntersector();

 protected:
    Scene &scene;
};

}

#endif //CRAYG_SCENEINTERSECTOR_H
