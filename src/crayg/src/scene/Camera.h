//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_CAMERA_H
#define CRAYG_CAMERA_H

#include <ostream>
#include "basics/Vector3f.h"
#include "sceneIO/Serializable.h"
#include "spdlog/fmt/ostr.h"

namespace crayg {

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

    float getHorizontalFieldOfView() const;

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

    bool operator==(const Camera &rhs) const;
    bool operator!=(const Camera &rhs) const;

    template<typename OStream>
    friend OStream &operator<<(OStream &os, const Camera &camera) {
        os << "Camera position: " << camera.position << " userUpVector: "
           << camera.userUpVector << " centerOfInterest: " << camera.centerOfInterest << " focalLength: "
           << camera.focalLength << " filmbackSize: " << camera.filmbackSize;
        return os;
    }
};

}
#endif //CRAYG_CAMERA_H
