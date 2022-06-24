#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHSCENEINTERSECTOR_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHSCENEINTERSECTOR_H_
#include "SceneIntersector.h"
#include "BvhNode.h"

namespace crayg {

class BvhSceneIntersector : public SceneIntersector {
 public:
    BvhSceneIntersector(Scene &scene, BvhNode *root);
    Imageable::Intersection intersect(const Ray &ray) const override;
    bool isIntersecting(const Ray &ray) const override;
    ~BvhSceneIntersector() override;
 private:
    BvhNode *root = nullptr;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHSCENEINTERSECTOR_H_
