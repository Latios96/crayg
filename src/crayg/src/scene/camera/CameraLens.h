#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_

#include "ThickLensApproximation.h"
#include "basics/Ray.h"
#include "utils/DtoUtils.h"
#include <fmt/ostream.h>
#include <functional>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace crayg {

CRAYG_DTO_2(LensElementIntersection, Vector3f, point, Vector3f, normal);

struct LensElement {
    LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius);

    float curvatureRadius;
    float thickness;
    float ior;
    float apertureRadius;
    float center;

    std::optional<LensElementIntersection> intersect(const Ray &ray);
    bool isAperture() const;
    bool exceedsAperture(const Ray &ray, float apertureRadius) const;
    bool exceedsAperture(const Vector3f &intersectionPosition) const;
    bool exceedsAperture(const Vector3f &intersectionPosition, float apertureRadius) const;
    bool operator==(const LensElement &rhs) const;
    bool operator!=(const LensElement &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const LensElement &element);
};

struct CameraLens {
    CameraLens(const std::string &name, const std::vector<LensElement> &elements);
    CameraLens(const CameraLens &cameraLens);
    std::string name;
    std::vector<LensElement> elements;
    ThickLensApproximation thickLensApproximation;
    float focalLength;

    const LensElement &getFirstElement() const;
    const LensElement &getLastElement() const;
    LensElement &getAperture();
    float getApertureRadius() const;

    std::optional<Ray> traceFromFilmToWorld(const Ray &ray) const;
    std::optional<Ray> traceFromWorldToFilm(const Ray &ray) const;

    void focusLens(float focalDistance);
    void moveLensElements(float offset);
    void changeAperture(float fStop);

    Ray refract(const LensElementIntersection &intersection, const Ray &ray, float iorIn, float iorOut) const;
    bool operator==(const CameraLens &rhs) const;
    bool operator!=(const CameraLens &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const CameraLens &lens);

  private:
    float getNextIor(int currentIndex, int indexOffset) const;
    std::optional<Ray> traceRay(const Ray &ray, int startIndex, std::function<int(int)> nextLensIndex,
                                std::function<float(int)> inIor, std::function<float(int)> outIor) const;
    int apertureIndex = -1;
    float apertureRadius;
};

} // crayg

template <> struct fmt::formatter<crayg::LensElement> : ostream_formatter {};

CRAYG_DTO_UTILS_VECTOR_FORMATTER(LensElement);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_
