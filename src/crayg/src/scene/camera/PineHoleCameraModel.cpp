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

Ray PineHoleCameraModel::createPrimaryRay(float x, float y) {
    const Vector3f pineHoleRayDirection = createPineHoleRayDirection(x, y);
    return {camera.getPosition(), camera.getTransform().applyForNormal(pineHoleRayDirection).normalize()};
}

Vector3f PineHoleCameraModel::createPineHoleRayDirection(float x, float y) {
    // TODO Note that always adding 0.5 is wrong, since this should be handled by the x,y generator.
    // TODO x and y should be passed with the correct position
    // TODO don't forget to check renderer code and PineHoleCamera
    float wScale = 2.0f * (x + 0.5f) / static_cast<float>(resolution.getWidth()) - 1.0f;
    float hScale = 2.0f * (y + 0.5f) / static_cast<float>(resolution.getHeight()) - 1.0f;

    return (viewVector + sideVector * wScale + upVector * hScale * -1).normalize();
}

}