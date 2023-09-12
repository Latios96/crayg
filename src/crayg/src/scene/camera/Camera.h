#ifndef CRAYG_CAMERA_H
#define CRAYG_CAMERA_H

#include "CameraType.h"
#include "basics/Vector3f.h"
#include "realistic/CameraLens.h"
#include "scene/Transformable.h"
#include "scene/camera/polynomial/PolynomialLenses.h"
#include "spdlog/fmt/ostr.h"
#include "utils/ToStringHelper.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

class Camera : public Transformable {
  private:
    float focalLength;
    float filmbackSize;
    std::string name;
    CameraType cameraType = CameraType::PINE_HOLE;
    float focusDistance = 0;
    float fStop = 0;
    std::optional<PolynomialLens> polynomialLens;

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
        return *lens;
    }

    const std::optional<PolynomialLens> &getPolynomialLens() const;
    void setPolynomialLens(const std::optional<PolynomialLens> &polynomialLens);

    bool operator==(const Camera &rhs) const;
    bool operator!=(const Camera &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Camera &camera) {
        os << ToStringHelper("Camera")
                  .addMember("transform", camera.transform)
                  .addMember("focalLength", camera.focalLength)
                  .addMember("filmbackSize", camera.filmbackSize)
                  .addMember("cameraType", camera.cameraType)
                  .addMember("focusDistance", camera.focusDistance)
                  .addMember("fStop", camera.fStop)
                  .finish();
        return os;
    }

    void setFocalLength(float focalLength);
    void setFilmbackSize(float filmbackSize);
};

}

template <> struct fmt::formatter<crayg::Camera> : ostream_formatter {};

#endif // CRAYG_CAMERA_H
