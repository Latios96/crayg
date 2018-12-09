//
// Created by jan on 16.08.18.
//

#include "Camera.h"

Camera::Camera(const Vector3f &position, const Vector3f &upVector, const Vector3f &centerOfInterest)
        : position(position), userUpVector(upVector), centerOfInterest(centerOfInterest) {}

const Vector3f &Camera::getPosition() const {
    return position;
}

const Vector3f &Camera::getUserUpVector() const {
    return userUpVector;
}

const Vector3f &Camera::getCenterOfInterest() const {
    return centerOfInterest;
}

float Camera::getFieldOfView() const {
    // based on https://www.vision-doctor.com/optik-berechnungen/oeffnungswinkel-berechnen.html
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

void Camera::setFocalLength(float focalLength) {
    Camera::focalLength = focalLength;
}

float Camera::getFilmbackSize() const {
    return filmbackSize;
}

void Camera::setFilmbackSize(float filmbackSize) {
    Camera::filmbackSize = filmbackSize;
}

Camera::Camera() = default;
