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
