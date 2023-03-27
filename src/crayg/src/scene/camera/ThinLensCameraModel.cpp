#include "ThinLensCameraModel.h"
#include "basics/Vector2.h"
#include "sampling/Sampling.h"

namespace crayg {
ThinLensCameraModel::ThinLensCameraModel(Camera &camera, const Resolution &resolution)
    : PineHoleCameraModel(camera, resolution) {
}

Ray ThinLensCameraModel::createPrimaryRay(float x, float y) { // todo add tests
    const Vector3f rayDirection = createPineHoleRayDirection(x, y);
    const float ft = camera.getFocusDistance() / rayDirection.z;
    const Vector3f pointOnFocalPlane = rayDirection * ft;
    auto apertureSample = Sampling::concentricSampleDisk() * camera.computeApertureSizeHeuristically();
    auto rayOrigin = Vector3f(apertureSample.x, apertureSample.y, 0);
    auto mutatedDirection = (pointOnFocalPlane - rayOrigin).normalize();
    return {camera.getPosition() + rayOrigin,
            camera.getTransform()
                .applyForNormal(mutatedDirection)
                .normalize()}; // todo add transformation for Ray, also check if we can improve this
}
} // crayg