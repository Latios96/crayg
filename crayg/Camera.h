//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_CAMERA_H
#define CRAYG_CAMERA_H


#include "Vector3f.h"

class Camera {
private:
    Vector3f position;
    Vector3f userUpVector;
    Vector3f centerOfInterest;
    float fieldOfView;

public:
    Camera(const Vector3f &position, const Vector3f &upVector, const Vector3f &centerOfInterest, float fieldOfView);

    const Vector3f &getPosition() const;

    const Vector3f &getUserUpVector() const;

    const Vector3f &getCenterOfInterest() const;

    float getFieldOfView() const;
};


#endif //CRAYG_CAMERA_H
