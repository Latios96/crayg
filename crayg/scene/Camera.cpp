//
// Created by jan on 16.08.18.
//

#include "Camera.h"

Camera::Camera(const Vector3f &position, const Vector3f &upVector, const Vector3f &centerOfInterest, float fieldOfView)
        : position(position), userUpVector(upVector), centerOfInterest(centerOfInterest), fieldOfView(fieldOfView) {}

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
    return fieldOfView;
}

void Camera::serialize(Serializer &serializer) {
    serializer.writeType("Camera");
    serializer.writeVector3f("position", position);
    serializer.writeVector3f("centerOfInterest", centerOfInterest);
    serializer.writeVector3f("userUpVector", userUpVector);
    serializer.writeFloat("fieldOfView", fieldOfView);
}

void Camera::deserialize(Deserializer &deserializer) {
    position = deserializer.readVector3f("position");
    centerOfInterest = deserializer.readVector3f("centerOfInterest");
    userUpVector = deserializer.readVector3f("userUpVector");
    fieldOfView = deserializer.readFloat("fieldOfView");
}

Camera::Camera() = default;
