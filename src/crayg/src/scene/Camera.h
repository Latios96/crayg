//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_CAMERA_H
#define CRAYG_CAMERA_H

#include "foundation/Vector3f.h"
#include "sceneIO/Serializable.h"

class Camera : public Serializable {
 private:
    Vector3f position;
    Vector3f userUpVector;
    Vector3f centerOfInterest;
    float focalLength;
    float filmbackSize;

 public:
    Camera();

    Camera(const Vector3f &position, const Vector3f &userUpVector, const Vector3f &centerOfInterest, float focalLength,
           float filmbackSize);

    const Vector3f &getPosition() const;

    const Vector3f &getUserUpVector() const;

    const Vector3f &getCenterOfInterest() const;
    /**
     * Returns FieldOfView based on focalLength and filmBackSize.
     * Calculation based on https://www.vision-doctor.com/optik-berechnungen/oeffnungswinkel-berechnen.html
     * @return FieldOfView in radians
     */
    float getFieldOfView() const;

    /**
     * Returns the focalLength in mm
     * @return focalLength in mm
     */
    float getFocalLength() const;
    /**
     * @return filmbackSize in mm
     */
    float getFilmbackSize() const;

    void serialize(Serializer &serializer) override;

    void deserialize(Deserializer &deserializer) override;
};

#endif //CRAYG_CAMERA_H
