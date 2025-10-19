#pragma once

#include "CameraType.h"
#include "crayg/foundation/assertions/Preconditions.h"
#include "crayg/foundation/math/geometry/Vector3f.h"
#include "realistic/CameraLens.h"
#include "scene/Transformable.h"
#include "spdlog/fmt/ostr.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

class Camera : public Transformable {
  private:
    float focalLength;
    float filmbackSize;
    std::string name;
    CameraType cameraType = CameraType::PINHOLE;
    float focusDistance = 0;
    float fStop = 0;

  public:
    std::unique_ptr<CameraLens> lens;

  public:
    Camera();

    Camera(const Transform &transform, float focalLength, float filmbackSize);

    Vector3f getUserUpVector() const;

    Vector3f getCenterOfInterest() const;

    float getHorizontalFieldOfView() const;

    float getFocalLength() const;

    float getFilmbackSize() const;

    const std::string &getName() const;
    void setName(const std::string &name);

    CameraType getCameraType() const;
    void setCameraType(CameraType cameraType);

    float getFocusDistance() const;
    void setFocusDistance(float focusDistance);

    float getFStop() const;
    void setFStop(float fStop);

    float computeApertureRadius() const;

    CameraLens &getLens() const {
        CRAYG_CHECKD_NOT_NULLPTR(lens);
        return *lens;
    }

    bool operator==(const Camera &rhs) const;
    bool operator!=(const Camera &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Camera &camera);

    void setFocalLength(float focalLength);
    void setFilmbackSize(float filmbackSize);
};

}

template <> struct fmt::formatter<crayg::Camera> : ostream_formatter {};
