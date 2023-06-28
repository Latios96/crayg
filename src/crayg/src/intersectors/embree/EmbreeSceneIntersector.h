#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREESCENEINTERSECTOR_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREESCENEINTERSECTOR_H_

#include "EmbreeBvh.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

class EmbreeSceneIntersector : public SceneIntersector {
  public:
    EmbreeSceneIntersector(Scene &scene, std::unique_ptr<EmbreeBvh> embreeBvh);
    Imageable::Intersection intersect(const Ray &ray) const override;
    bool isOccluded(const Ray &ray, float maxDistance) const override;
    ~EmbreeSceneIntersector() override;

  private:
    std::unique_ptr<EmbreeBvh> embreeBvh;
    Imageable::Intersection map(GeomToSceneObject &geomIdToSceneObject, RTCRayHit &rtcRayHit,
                                const std::vector<std::shared_ptr<SceneObject>> &objects,
                                Transform *instanceTransform) const;
    Imageable::Intersection mapToTriangle(const RTCRayHit &rtcRayHit, const EmbreeMappingEntry &embreeMappingEntry,
                                          const std::vector<std::shared_ptr<SceneObject>> &objects,
                                          Transform *instanceTransform) const;
    Imageable::Intersection mapToSubdivisionSurfaceMesh(const RTCRayHit &rtcRayHit,
                                                        const EmbreeMappingEntry &embreeMappingEntry,
                                                        const std::vector<std::shared_ptr<SceneObject>> &objects,
                                                        Transform *instanceTransform) const;
    Imageable::Intersection mapToSphere(const RTCRayHit &rtcRayHit, const EmbreeMappingEntry &embreeMappingEntry,
                                        const std::vector<std::shared_ptr<SceneObject>> &objects) const;
    Imageable::Intersection mapToInstancedSphere(const RTCRayHit &rtcRayHit,
                                                 const EmbreeMappingEntry &embreeMappingEntry,
                                                 const std::vector<std::shared_ptr<SceneObject>> &objects,
                                                 Transform *instanceTransform) const;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREESCENEINTERSECTOR_H_
