#include "ThinLensCameraModel.h"
#include "sampling/Sampling.h"

namespace crayg {
ThinLensCameraModel::ThinLensCameraModel(Camera &camera, const Resolution &resolution)
    : PineHoleCameraModel(camera, resolution) {
}

RayWithWeight ThinLensCameraModel::createPrimaryRay(float x, float y, float wavelength) { // todo add tests
    const Vector3f rayDirection = createPineHoleRayDirection(x, y);
    const float ft = camera.getFocusDistance() / rayDirection.z;
    const Vector3f pointOnFocalPlane = rayDirection * ft;
    auto apertureSample = Sampling::concentricSampleDisk() * camera.computeApertureRadius();
    auto rayOrigin = Vector3f(apertureSample.x, apertureSample.y, 0);
    auto mutatedDirection = (pointOnFocalPlane - rayOrigin).normalize();
    return {camera.getTransform().apply(Ray(rayOrigin, mutatedDirection)), 1};
}
} // crayg