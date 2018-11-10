//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_CAMERA_H
#define CRAYG_CAMERA_H


#include "foundation/Vector3f.h"
#include "sceneIO/Serializable.h"

class Camera : public Serializable{
private:
    Vector3f position;
    Vector3f userUpVector;
    Vector3f centerOfInterest;
    float fieldOfView;

public:
    Camera();
    Camera(const Vector3f &position, const Vector3f &upVector, const Vector3f &centerOfInterest, float fieldOfView);

    const Vector3f &getPosition() const;

    const Vector3f &getUserUpVector() const;

    const Vector3f &getCenterOfInterest() const;
    // todo how to we expect the
    float getFieldOfView() const;

    void serialize(Serializer& serializer) override;

    void deserialize(Deserializer& deserializer) override;
};


#endif //CRAYG_CAMERA_H
