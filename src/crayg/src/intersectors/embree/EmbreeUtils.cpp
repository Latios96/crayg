#include "EmbreeUtils.h"

namespace crayg {

void EmbreeUtils::createRTCRayHit(const Ray &ray, RTCRayHit *rtcRayHit, float tFar) {
    createRtcRay(ray, &rtcRayHit->ray, tFar);
    rtcRayHit->hit.geomID = RTC_INVALID_GEOMETRY_ID;
}

void EmbreeUtils::createRtcRay(const Ray &ray, RTCRay *rtcRay, float tFar) {
    rtcRay->org_x = ray.startPoint.x;
    rtcRay->org_y = ray.startPoint.y;
    rtcRay->org_z = ray.startPoint.z;
    rtcRay->tnear = 0.001f;
    rtcRay->dir_x = ray.direction.x;
    rtcRay->dir_y = ray.direction.y;
    rtcRay->dir_z = ray.direction.z;
    rtcRay->tfar = tFar;
}

}