//
// Created by jan on 16.08.18.
//

#include "Camera.h"

namespace crayg {

Camera::Camera(const Vector3f &position, const Vector3f &userUpVector, const Vector3f &centerOfInterest,
               float focalLength, float filmbackSize) : position(position), userUpVector(userUpVector),
                                                        centerOfInterest(centerOfInterest), focalLength(focalLength),
                                                        filmbackSize(filmbackSize) {}

Camera::Camera() = default;

const Vector3f &Camera::getPosition() const {
    return position;
}

const Vector3f &Camera::getUserUpVector() const {
    return userUpVector;
}

const Vector3f &Camera::getCenterOfInterest() const {
    return centerOfInterest;
}

float Camera::getHorizontalFieldOfView() const {
    // based on https://github.com/PixarAnimationStudios/USD/blob/090ef0d849ced875b3b99a15e454b69148ccd8e1/pxr/base/gf/camera.cpp#L303
    return 2 * std::atan(filmbackSize / 2.0f * 1.0f / focalLength);
}

void Camera::serialize(Serializer &serializer) {
    serializer.writeType("Camera");
    serializer.writeVector3f("position", position);
    serializer.writeVector3f("centerOfInterest", centerOfInterest);
    serializer.writeVector3f("userUpVector", userUpVector);
    serializer.writeFloat("focalLength", focalLength);
    serializer.writeFloat("filmbackSize", filmbackSize);
}

void Camera::deserialize(Deserializer &deserializer) {
    position = deserializer.readVector3f("position");
    centerOfInterest = deserializer.readVector3f("centerOfInterest");
    userUpVector = deserializer.readVector3f("userUpVector");
    focalLength = deserializer.readFloat("focalLength");
    filmbackSize = deserializer.readFloat("filmbackSize");
}

float Camera::getFocalLength() const {
    return focalLength;
}

float Camera::getFilmbackSize() const {
    return filmbackSize;
}

}




