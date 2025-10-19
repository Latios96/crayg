#pragma once

#include "EmbreeBvh.h"
#include "crayg/renderer/intersectors/SceneIntersector.h"

namespace crayg {

class EmbreeSceneIntersector : public SceneIntersector {
  public:
    EmbreeSceneIntersector(Scene &scene, std::unique_ptr<EmbreeBvh> embreeBvh);
    Imageable::Intersection intersect(const Ray &ray, HitStorage &hitStorage) const override;
    bool isOccluded(const Ray &ray, HitStorage &hitStorage, float maxDistance) const override;
    ~EmbreeSceneIntersector() override;

  private:
    std::unique_ptr<EmbreeBvh> embreeBvh;
    Imageable::Intersection map(GeomToSceneObject &geomIdToSceneObject, RTCRayHit &rtcRayHit,
                                const std::vector<std::shared_ptr<SceneObject>> &objects, Transform *instanceTransform,
                                HitStorage &hitStorage) const;
    Imageable::Intersection mapToTriangle(const RTCRayHit &rtcRayHit, const EmbreeMappingEntry &embreeMappingEntry,
                                          const std::vector<std::shared_ptr<SceneObject>> &objects,
                                          Transform *instanceTransform, HitStorage &hitStorage) const;
    Imageable::Intersection mapToSubdivisionSurfaceMesh(const RTCRayHit &rtcRayHit,
                                                        const EmbreeMappingEntry &embreeMappingEntry,
                                                        const std::vector<std::shared_ptr<SceneObject>> &objects,
                                                        Transform *instanceTransform, HitStorage &hitStorage) const;
    Imageable::Intersection mapToSphere(const RTCRayHit &rtcRayHit, const EmbreeMappingEntry &embreeMappingEntry,
                                        const std::vector<std::shared_ptr<SceneObject>> &objects) const;
    Imageable::Intersection mapToInstancedSphere(const RTCRayHit &rtcRayHit,
                                                 const EmbreeMappingEntry &embreeMappingEntry,
                                                 const std::vector<std::shared_ptr<SceneObject>> &objects,
                                                 Transform *instanceTransform, HitStorage &hitStorage) const;
    Imageable::Intersection mapToLight(const RTCRayHit &rtcRayHit,
                                       const crayg::EmbreeMappingEntry &embreeMappingEntry) const;
};

}
