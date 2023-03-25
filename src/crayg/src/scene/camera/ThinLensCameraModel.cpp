#include "ThinLensCameraModel.h"
#include "basics/Vector2.h"
#include "sampling/Sampling.h"

namespace crayg {
ThinLensCameraModel::ThinLensCameraModel(Camera &camera, const Resolution &resolution)
    : PineHoleCameraModel(camera, resolution) {
}

Ray ThinLensCameraModel::createPrimaryRay(float x, float y) {
    const Vector3f rayDirection = calculateRayDirection(x, y);
    const float ft = camera.getFocusDistance() / rayDirection.z;
    const Vector3f pointOnFocalPlane = rayDirection * ft;
    auto apertureSample = Sampling::concentricSampleDisk() * camera.getFStop();
    auto rayOrigin = Vector3f(apertureSample.x, apertureSample.y, 0);
    auto mutatedDirection = (pointOnFocalPlane - rayOrigin).normalize();
    return {camera.getPosition() + rayOrigin,
            camera.getTransform().applyForNormal(mutatedDirection).normalize()}; // todo add transformation for Ray
}

Vector3f ThinLensCameraModel::calculateRayDirection(float x, float y) { // todo clean this up in PineHoleCamera
    float imageRatio = static_cast<float>(resolution.getWidth()) / static_cast<float>(resolution.getHeight());

    // create view position
    const Vector3f &centerOfInterest = {0, 0, 1};
    const Vector3f &position = {0, 0, 0};
    Vector3f viewVector = {0, 0, 1};

    // create site position
    Vector3f sideVector = {1, 0, 0};

    // create camera up position, user up position might not be orthononal to viewVector
    Vector3f upVector = {0, 1, 0};

    // create width and height, define the size of the view plane
    auto imagePlaneHeight = (2.0f * std::tan(camera.getHorizontalFieldOfView() / 2.0f)) / imageRatio;

    auto imagePlaneWidth = imageRatio * imagePlaneHeight;

    // should have length of image plane
    sideVector = sideVector * (imagePlaneWidth / 2.0f);
    // upVector should have length of imagePlane
    upVector = upVector * (imagePlaneHeight / 2.0f);

    auto planeCenter = viewVector;
    float wScale = 2.0f * (x + 0.5f) / static_cast<float>(resolution.getWidth()) - 1.0f;
    float hScale = 2.0f * (y + 0.5f) / static_cast<float>(resolution.getHeight()) - 1.0f;

    return planeCenter + sideVector * wScale + upVector * hScale * -1;
}
} // crayg