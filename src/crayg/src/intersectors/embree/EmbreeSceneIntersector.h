#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREESCENEINTERSECTOR_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREESCENEINTERSECTOR_H_

#include "intersectors/SceneIntersector.h"
#include "EmbreeBvh.h"

namespace crayg {

class EmbreeSceneIntersector : public SceneIntersector {
 public:
    EmbreeSceneIntersector(Scene &scene, std::unique_ptr<EmbreeBvh> embreeBvh);
    Imageable::Intersection intersect(const Ray &ray) const override;
    bool isIntersecting(const Ray &ray) const override;
    ~EmbreeSceneIntersector() override;
 private:
    std::unique_ptr<EmbreeBvh> embreeBvh;
    Imageable::Intersection mapToTriangle(const RTCRayHit &rtcRayHit,
                                          const EmbreeMappingEntry &embreeMappingEntry) const;
    Imageable::Intersection mapToSphere(const RTCRayHit &rtcRayHit,
                                        const EmbreeMappingEntry &embreeMappingEntry) const;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREESCENEINTERSECTOR_H_
