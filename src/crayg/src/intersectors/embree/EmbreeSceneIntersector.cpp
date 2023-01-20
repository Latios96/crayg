#include "EmbreeSceneIntersector.h"
#include "EmbreeUtils.h"

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
    if (sceneObjectMapping.second == EmbreePrimitiveType::TRIANGLE_MESH) {
        return mapToTriangle(rtcRayHit, sceneObjectMapping);
    } else if (sceneObjectMapping.second == EmbreePrimitiveType::SPHERE) {
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
                                                            const std::pair<unsigned int,
                                                                            EmbreePrimitiveType> &sceneObjectMapping) const {
    auto sceneObject = scene.objects[sceneObjectMapping.first];
    return Imageable::Intersection(rtcRayHit.ray.tfar, sceneObject.get(), false);
}

Imageable::Intersection EmbreeSceneIntersector::mapToTriangle(const RTCRayHit &rtcRayHit,
                                                              const std::pair<unsigned int,
                                                                              EmbreePrimitiveType> &sceneObjectMapping) const {
    auto sceneObject = scene.objects[sceneObjectMapping.first];
    auto triangleMesh = std::dynamic_pointer_cast<TriangleMesh>(sceneObject);
    auto triangle =
        new Triangle(triangleMesh.get(), rtcRayHit.hit.primID);
    return Imageable::Intersection(rtcRayHit.ray.tfar, triangle, true);
}

EmbreeSceneIntersector::~EmbreeSceneIntersector() {

}
EmbreeSceneIntersector::EmbreeSceneIntersector(Scene &scene, std::unique_ptr<EmbreeBvh> embreeBvh)
    : SceneIntersector(scene), embreeBvh(std::move(embreeBvh)) {}
} // crayg