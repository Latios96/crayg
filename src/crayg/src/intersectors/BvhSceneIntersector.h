#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHSCENEINTERSECTOR_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHSCENEINTERSECTOR_H_
#include "SceneIntersector.h"
#include "BvhNode.h"
#include "BvhBuilder.h"

namespace crayg {

class BvhSceneIntersector : public SceneIntersector {
 public:
    BvhSceneIntersector(Scene &scene, std::unique_ptr<Bvh> bvh);
    Imageable::Intersection intersect(const Ray &ray) const override;
    bool isIntersecting(const Ray &ray) const override;
    ~BvhSceneIntersector() override = default;
 private:
    std::unique_ptr<Bvh> bvh = nullptr;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHSCENEINTERSECTOR_H_
