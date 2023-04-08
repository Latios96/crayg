#include "Camera.h"
#include "utils/ToStringHelper.h"

namespace crayg {

Camera::Camera(const Transform &transform, float focalLength, float filmbackSize)
    : Transformable(transform), focalLength(focalLength), filmbackSize(filmbackSize) {
}

Camera::Camera() = default;

Vector3f Camera::getUserUpVector() const {
    return {0, 1, 0};
}

Vector3f Camera::getCenterOfInterest() const {
    return transform.applyForPoint({0, 0, 1});
}

float Camera::getHorizontalFieldOfView() const {
    // based on
    // https://github.com/PixarAnimationStudios/USD/blob/090ef0d849ced875b3b99a15e454b69148ccd8e1/pxr/base/gf/camera.cpp#L303
    return 2 * std::atan(filmbackSize / 2.0f * 1.0f / focalLength);
}

float Camera::getFocalLength() const {
    return focalLength;
}

float Camera::getFilmbackSize() const {
    return filmbackSize;
}

bool Camera::operator==(const Camera &rhs) const {
    return transform == rhs.transform && focalLength == rhs.focalLength && filmbackSize == rhs.filmbackSize &&
           cameraType == rhs.cameraType && focusDistance == rhs.focusDistance && fStop == rhs.fStop;
}

bool Camera::operator!=(const Camera &rhs) const {
    return !(rhs == *this);
}

void Camera::setFocalLength(float focalLength) {
    Camera::focalLength = focalLength;
}

void Camera::setFilmbackSize(float filmbackSize) {
    Camera::filmbackSize = filmbackSize;
}

const std::string &Camera::getName() const {
    return name;
}

void Camera::setName(const std::string &name) {
    Camera::name = name;
}

CameraType Camera::getCameraType() const {
    return cameraType;
}

void Camera::setCameraType(CameraType cameraType) {
    Camera::cameraType = cameraType;
}

float Camera::getFocusDistance() const {
    return focusDistance;
}

void Camera::setFocusDistance(float focusDistance) {
    Camera::focusDistance = focusDistance;
}

float Camera::getFStop() const {
    return fStop;
}

void Camera::setFStop(float fStop) {
    Camera::fStop = fStop;
}

float Camera::computeApertureRadius() const {
    // see "Optical Imaging and Photography", p. 67
    return (focalLength * 0.1f / fStop) / 2.0f;
}

}
