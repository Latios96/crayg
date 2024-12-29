#include "EmbreeSceneIntersector.h"
#include "EmbreeUtils.h"
#include "scene/primitives/PointInstancer.h"
#include "scene/primitives/Sphere.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"

namespace crayg {

Imageable::Intersection EmbreeSceneIntersector::intersect(const Ray &ray, HitStorage &hitStorage) const {
    RTCIntersectContext context;
    rtcInitIntersectContext(&context);

    RTCRayHit rtcRayHit;
    EmbreeUtils::createRTCRayHit(ray, &rtcRayHit);

    rtcIntersect1(embreeBvh->rtcScene, &context, &rtcRayHit);

    const bool hasHit = rtcRayHit.hit.geomID != RTC_INVALID_GEOMETRY_ID;
    if (!hasHit) {
        return Imageable::Intersection::createInvalid();
    }

    if (rtcRayHit.hit.instID[0] != RTC_INVALID_GEOMETRY_ID) {
        auto instanceId = rtcRayHit.hit.instID[0];
        auto embreeInstanceInfo = embreeBvh->embreeInstanceIdToInstanceInfo[instanceId];
        auto &instanceMappingEntry = embreeBvh->globalProtoGeomToSceneObject[embreeInstanceInfo.globalProtoId];
        auto pointInstancer =
            std::dynamic_pointer_cast<PointInstancer>(scene.objects[instanceMappingEntry.pointInstancerIndex]);
        auto &members = pointInstancer->protos[instanceMappingEntry.protoId]->members;
        return map(instanceMappingEntry.geomToSceneObject, rtcRayHit, members,
                   &pointInstancer->transforms[embreeInstanceInfo.instanceId], hitStorage);
    }

    return map(embreeBvh->geomIdToSceneObject, rtcRayHit, scene.objects, nullptr, hitStorage);
}

bool EmbreeSceneIntersector::isOccluded(const Ray &ray, HitStorage &hitStorage, float maxDistance) const {
    RTCIntersectContext context;
    rtcInitIntersectContext(&context);

    RTCRayHit rtcRayHit;
    EmbreeUtils::createRTCRayHit(ray, &rtcRayHit, maxDistance);

    rtcOccluded1(embreeBvh->rtcScene, &context, &rtcRayHit.ray);

    return rtcRayHit.ray.tfar < 0;
}

Imageable::Intersection EmbreeSceneIntersector::map(GeomToSceneObject &geomIdToSceneObject, RTCRayHit &rtcRayHit,
                                                    const std::vector<std::shared_ptr<SceneObject>> &objects,
                                                    Transform *instanceTransform, HitStorage &hitStorage) const {
    const auto sceneObjectMapping = geomIdToSceneObject[rtcRayHit.hit.geomID];
    if (sceneObjectMapping.primitiveType == EmbreePrimitiveType::TRIANGLE_MESH) {
        return mapToTriangle(rtcRayHit, sceneObjectMapping, objects, instanceTransform, hitStorage);
    } else if (sceneObjectMapping.primitiveType == EmbreePrimitiveType::SUBDIVISION_SURFACE_MESH) {
        return mapToSubdivisionSurfaceMesh(rtcRayHit, sceneObjectMapping, objects, instanceTransform, hitStorage);
    } else if (sceneObjectMapping.primitiveType == EmbreePrimitiveType::SPHERE) {
        if (instanceTransform) {
            return mapToInstancedSphere(rtcRayHit, sceneObjectMapping, objects, instanceTransform, hitStorage);
        }
        return mapToSphere(rtcRayHit, sceneObjectMapping, objects);
    } else if (sceneObjectMapping.primitiveType == EmbreePrimitiveType::LIGHT) {
        return mapToLight(rtcRayHit, sceneObjectMapping);
    }

    return Imageable::Intersection::createInvalid();
}

Imageable::Intersection
EmbreeSceneIntersector::mapToSphere(const RTCRayHit &rtcRayHit, const EmbreeMappingEntry &embreeMappingEntry,
                                    const std::vector<std::shared_ptr<SceneObject>> &objects) const {
    auto sceneObject = objects[embreeMappingEntry.sceneObjectIndex];
    return {rtcRayHit.ray.tfar, sceneObject.get()};
}

Imageable::Intersection
EmbreeSceneIntersector::mapToInstancedSphere(const RTCRayHit &rtcRayHit, const EmbreeMappingEntry &embreeMappingEntry,
                                             const std::vector<std::shared_ptr<SceneObject>> &objects,
                                             Transform *instanceTransform, HitStorage &hitStorage) const {
    auto sceneObject = objects[embreeMappingEntry.sceneObjectIndex];
    auto sphere = std::dynamic_pointer_cast<Sphere>(sceneObject);
    hitStorage.sphere = Sphere();
    auto instancedSphere = &hitStorage.sphere;
    instancedSphere->setTransform(*instanceTransform * sphere->getTransform());
    instancedSphere->setRadius(sphere->getRadius());
    return {rtcRayHit.ray.tfar, instancedSphere};
}

Imageable::Intersection EmbreeSceneIntersector::mapToTriangle(const RTCRayHit &rtcRayHit,
                                                              const EmbreeMappingEntry &embreeMappingEntry,
                                                              const std::vector<std::shared_ptr<SceneObject>> &objects,
                                                              Transform *instanceTransform,
                                                              HitStorage &hitStorage) const {
    auto sceneObject = objects[embreeMappingEntry.sceneObjectIndex];
    auto triangleMesh = std::dynamic_pointer_cast<TriangleMesh>(sceneObject);
    hitStorage.triangle = Triangle(triangleMesh.get(), rtcRayHit.hit.primID, instanceTransform);
    auto triangle = &hitStorage.triangle;
    return {rtcRayHit.ray.tfar, triangle};
}

Imageable::Intersection
EmbreeSceneIntersector::mapToSubdivisionSurfaceMesh(const RTCRayHit &rtcRayHit,
                                                    const EmbreeMappingEntry &embreeMappingEntry,
                                                    const std::vector<std::shared_ptr<SceneObject>> &objects,
                                                    Transform *instanceTransform, HitStorage &hitStorage) const {
    auto sceneObject = objects[embreeMappingEntry.sceneObjectIndex];
    auto subdivisionSurfaceMesh = std::dynamic_pointer_cast<SubdivisionSurfaceMesh>(sceneObject);
    hitStorage.triangle = Triangle(&subdivisionSurfaceMesh->triangleMesh, rtcRayHit.hit.primID, instanceTransform);
    auto triangle = &hitStorage.triangle;
    return {rtcRayHit.ray.tfar, triangle};
}

Imageable::Intersection EmbreeSceneIntersector::mapToLight(const RTCRayHit &rtcRayHit,
                                                           const crayg::EmbreeMappingEntry &embreeMappingEntry) const {
    auto sceneObject = scene.lights[embreeMappingEntry.sceneObjectIndex];
    return {rtcRayHit.ray.tfar, sceneObject.get()};
}

EmbreeSceneIntersector::~EmbreeSceneIntersector() = default;

EmbreeSceneIntersector::EmbreeSceneIntersector(Scene &scene, std::unique_ptr<EmbreeBvh> embreeBvh)
    : SceneIntersector(scene), embreeBvh(std::move(embreeBvh)) {
}

} // crayg