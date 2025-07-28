#include "ThinLensCameraModel.h"
#include "sampling/Sampling.h"

namespace crayg {
ThinLensCameraModel::ThinLensCameraModel(Camera &camera, const Resolution &resolution)
    : PinholeCameraModel(camera, resolution) {
}

RayWithWeight ThinLensCameraModel::createPrimaryRay(const Vector2f &pixelPos, float wavelength) { // todo add tests
    const Vector3f rayDirection = createPinholeRayDirection(pixelPos);
    const float ft = camera.getFocusDistance() / rayDirection.z;
    const Vector3f pointOnFocalPlane = rayDirection * ft;
    auto apertureSample = Sampling::concentricSampleDisk() * camera.computeApertureRadius();
    auto rayOrigin = Vector3f(apertureSample.x, apertureSample.y, 0);
    auto mutatedDirection = (pointOnFocalPlane - rayOrigin).normalize();
    const Transform &transform = camera.getTransform();
    return {transform.apply(Ray(rayOrigin, mutatedDirection)), 1};
}
}