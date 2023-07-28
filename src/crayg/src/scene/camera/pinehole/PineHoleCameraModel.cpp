#include "PineHoleCameraModel.h"
#include <cmath>

namespace crayg {

PineHoleCameraModel::PineHoleCameraModel(Camera &camera, const Resolution &resolution)
    : CameraModel(camera, resolution) {
    imageRatio = static_cast<float>(resolution.getWidth()) / static_cast<float>(resolution.getHeight());
    imagePlaneHeight = (2.0f * std::tan(camera.getHorizontalFieldOfView() / 2.0f)) / imageRatio;
    imagePlaneWidth = imageRatio * imagePlaneHeight;
    sideVector = sideVector * (imagePlaneWidth / 2.0f);
    upVector = upVector * (imagePlaneHeight / 2.0f);
}

RayWithWeight PineHoleCameraModel::createPrimaryRay(float x, float y) {
    const Vector3f pineHoleRayDirection = createPineHoleRayDirection(x, y);
    return {Ray(camera.getPosition(), camera.getTransform().applyForNormal(pineHoleRayDirection).normalize()), 1};
}

Vector3f PineHoleCameraModel::createPineHoleRayDirection(float x, float y) {
    float wScale = 2.0f * x / static_cast<float>(resolution.getWidth()) - 1.0f;
    float hScale = 2.0f * y / static_cast<float>(resolution.getHeight()) - 1.0f;

    return (viewVector + sideVector * wScale + upVector * hScale * -1).normalize();
}

}