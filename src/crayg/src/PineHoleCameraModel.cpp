#include <cmath>
#include "PineHoleCameraModel.h"

namespace crayg {

PineHoleCameraModel::PineHoleCameraModel(Camera &camera, int imageWidth, int imageHeight) : camera(camera),
                                                                                            imageWidth(imageWidth),
                                                                                            imageHeight(imageHeight) {
    imageRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);

    // create view position
    const Vector3f &centerOfInterest = camera.getCenterOfInterest();
    const Vector3f &position = camera.getPosition();
    viewVector = centerOfInterest.substract(position).normalize();

    // create site position
    sideVector = viewVector.cross(camera.getUserUpVector()).normalize();

    // create camera up position, user up position might not be orthononal to viewVector
    upVector = sideVector.cross(viewVector).normalize();

    // create width and height, define the size of the view plane
    imagePlaneHeight = (2.0f * std::tan(camera.getHorizontalFieldOfView() / 2.0f)) / imageRatio;

    imagePlaneWidth = imageRatio * imagePlaneHeight;

    // should have length of image plane
    sideVector = sideVector.multiplyScalar(imagePlaneWidth / 2.0f);
    // upVector should have length of imagePlane
    upVector = upVector.multiplyScalar(imagePlaneHeight / 2.0f);

    planeCenter = camera.getPosition().add(viewVector);
}

Ray PineHoleCameraModel::createPrimaryRay(float x, float y) {
    Vector3f pixelCenter = getPixelCenter(x, y);
    Vector3f rayDirection = pixelCenter.substract(camera.getPosition()).normalize();
    return {camera.getPosition(), rayDirection};
}

Vector3f PineHoleCameraModel::getPixelCenter(float x, float y) {
    float wScale = 2.0f * (x + 0.5f) / static_cast<float>(imageWidth) - 1.0f;
    float hScale = 2.0f * (y + 0.5f) / static_cast<float>(imageHeight) - 1.0f;

    return planeCenter.add(sideVector.multiplyScalar(wScale * -1)).add(upVector.multiplyScalar(hScale * -1));
}

}