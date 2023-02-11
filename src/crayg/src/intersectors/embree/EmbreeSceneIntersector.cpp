#include "EmbreeSceneIntersector.h"
#include "EmbreeUtils.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"

namespace crayg {

Imageable::Intersection EmbreeSceneIntersector::intersect(const Ray &ray) const {
    RTCIntersectContext context;
    rtcInitIntersectContext(&context);

    RTCRayHit rtcRayHit;
    EmbreeUtils::createRTCRayHit(ray, &rtcRayHit);

    rtcIntersect1(embreeBvh->rtcScene, &context, &rtcRayHit);

    const bool hasHit = rtcRayHit.hit.geomID != RTC_INVALID_GEOMETRY_ID;
    if (!hasHit) {
        return Imageable::Intersection::createInvalid();
    }

    const auto sceneObjectMapping = embreeBvh->geomIdToSceneObject[rtcRayHit.hit.geomID];
    if (sceneObjectMapping.primitiveType == EmbreePrimitiveType::TRIANGLE_MESH) {
        return mapToTriangle(rtcRayHit, sceneObjectMapping);
    } else if (sceneObjectMapping.primitiveType == EmbreePrimitiveType::SUBDIVISION_SURFACE_MESH) {
        return mapToSubdivisionSurfaceMesh(rtcRayHit, sceneObjectMapping);
    } else if (sceneObjectMapping.primitiveType == EmbreePrimitiveType::SPHERE) {
        return mapToSphere(rtcRayHit, sceneObjectMapping);
    }
    return Imageable::Intersection::createInvalid();
}
bool EmbreeSceneIntersector::isIntersecting(const Ray &ray) const {
    RTCIntersectContext context;
    rtcInitIntersectContext(&context);

    RTCRayHit rtcRayHit;
    EmbreeUtils::createRTCRayHit(ray, &rtcRayHit);

    rtcOccluded1(embreeBvh->rtcScene, &context, &rtcRayHit.ray);

    return rtcRayHit.ray.tfar < 0;
}

Imageable::Intersection EmbreeSceneIntersector::mapToSphere(const RTCRayHit &rtcRayHit,
                                                            const EmbreeMappingEntry &embreeMappingEntry) const {
    auto sceneObject = scene.objects[embreeMappingEntry.sceneObjectIndex];
    return {rtcRayHit.ray.tfar, sceneObject.get(), false};
}

Imageable::Intersection EmbreeSceneIntersector::mapToTriangle(const RTCRayHit &rtcRayHit,
                                                              const EmbreeMappingEntry &embreeMappingEntry) const {
    auto sceneObject = scene.objects[embreeMappingEntry.sceneObjectIndex];
    auto triangleMesh = std::dynamic_pointer_cast<TriangleMesh>(sceneObject);
    auto triangle =
        new Triangle(triangleMesh.get(), rtcRayHit.hit.primID);
    return {rtcRayHit.ray.tfar, triangle, true};
}

Imageable::Intersection EmbreeSceneIntersector::mapToSubdivisionSurfaceMesh(const RTCRayHit &rtcRayHit,
                                                                            const EmbreeMappingEntry &embreeMappingEntry) const {
    auto sceneObject = scene.objects[embreeMappingEntry.sceneObjectIndex];
    auto subdivisionSurfaceMesh = std::dynamic_pointer_cast<SubdivisionSurfaceMesh>(sceneObject);
    auto triangle =
        new Triangle(&subdivisionSurfaceMesh->triangleMesh, rtcRayHit.hit.primID);
    return {rtcRayHit.ray.tfar, triangle, true};
}

EmbreeSceneIntersector::~EmbreeSceneIntersector() = default;

EmbreeSceneIntersector::EmbreeSceneIntersector(Scene &scene, std::unique_ptr<EmbreeBvh> embreeBvh)
    : SceneIntersector(scene), embreeBvh(std::move(embreeBvh)) {}
} // crayg