#include "EmbreeSceneIntersector.h"

namespace crayg {
Imageable::Intersection EmbreeSceneIntersector::intersect(const Ray &ray) const {
    RTCIntersectContext context;
    rtcInitIntersectContext(&context);

    RTCRayHit rtcRayHit;

    rtcRayHit.ray.org_x = ray.startPoint.x;
    rtcRayHit.ray.org_y = ray.startPoint.y;
    rtcRayHit.ray.org_z = ray.startPoint.z;
    rtcRayHit.ray.tnear = 0.001f;
    rtcRayHit.ray.dir_x = ray.direction.x;
    rtcRayHit.ray.dir_y = ray.direction.y;
    rtcRayHit.ray.dir_z = ray.direction.z;
    rtcRayHit.ray.tfar = std::numeric_limits<float>::infinity();
    rtcRayHit.hit.geomID = RTC_INVALID_GEOMETRY_ID;

    rtcIntersect1(embreeBvh->rtcScene, &context, &rtcRayHit);

    const bool hasHit = rtcRayHit.hit.geomID != RTC_INVALID_GEOMETRY_ID;
    if (!hasHit) {
        return Imageable::Intersection::createInvalid();
    }

    const auto sceneObjectMapping = embreeBvh->geomIdToSceneObject[rtcRayHit.hit.geomID];
    if (sceneObjectMapping.second == EmbreePrimitiveType::TRIANGLE) {
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

    rtcRayHit.ray.org_x = ray.startPoint.x;
    rtcRayHit.ray.org_y = ray.startPoint.y;
    rtcRayHit.ray.org_z = ray.startPoint.z;
    rtcRayHit.ray.tnear = 0.001f;
    rtcRayHit.ray.dir_x = ray.direction.x;
    rtcRayHit.ray.dir_y = ray.direction.y;
    rtcRayHit.ray.dir_z = ray.direction.z;
    rtcRayHit.ray.tfar = std::numeric_limits<float>::infinity();
    rtcRayHit.hit.geomID = RTC_INVALID_GEOMETRY_ID;

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