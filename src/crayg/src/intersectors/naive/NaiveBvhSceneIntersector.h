#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHSCENEINTERSECTOR_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHSCENEINTERSECTOR_H_
#include "NaiveBvhBuilder.h"
#include "NaiveBvhNode.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

class NaiveBvhSceneIntersector : public SceneIntersector {
  public:
    NaiveBvhSceneIntersector(Scene &scene, std::unique_ptr<NaiveBvh> bvh);
    Imageable::Intersection intersect(const Ray &ray) const override;
    bool isIntersecting(const Ray &ray) const override;
    ~NaiveBvhSceneIntersector() override = default;

  private:
    std::unique_ptr<NaiveBvh> bvh = nullptr;
};

}

#endif // CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHSCENEINTERSECTOR_H_
