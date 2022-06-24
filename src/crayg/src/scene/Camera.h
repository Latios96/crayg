//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_CAMERA_H
#define CRAYG_CAMERA_H

#include <ostream>
#include "basics/Vector3f.h"
#include "scene/Transformable.h"
#include "spdlog/fmt/ostr.h"
#include "utils/ToStringHelper.h"

namespace crayg {

class Camera : public Transformable {
 private:
    float focalLength;
    float filmbackSize;
    std::string name;

 public:
    Camera();

    Camera(const Transform &transform, float focalLength, float filmbackSize);
    //const Vector3f &getPosition() const;

    Vector3f getUserUpVector() const;

    Vector3f getCenterOfInterest() const;

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

    const std::string &getName() const;
    void setName(const std::string &name);

    bool operator==(const Camera &rhs) const;
    bool operator!=(const Camera &rhs) const;

    //template<typename OStream>
    friend std::ostream &operator<<(std::ostream &os, const Camera &camera) {
        os << ToStringHelper("Camera")
            .addMember("transform", camera.transform)
            .addMember("focalLength", camera.focalLength)
            .addMember("filmbackSize", camera.filmbackSize)
            .finish();
        return os;
    }

    void setFocalLength(float focalLength);
    void setFilmbackSize(float filmbackSize);
};

}
#endif //CRAYG_CAMERA_H
