#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_

#include "LensGeometry.h"
#include "LensMaterial.h"
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
    LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
                LensMaterial lensMaterial, LensGeometry geometry);

    float curvatureRadius;
    float thickness;
    float ior;
    float apertureRadius;
    float center;
    float abbeNumber;
    LensMaterial material;
    LensGeometry geometry;

    bool isAperture() const;

    bool operator==(const LensElement &rhs) const;
    bool operator!=(const LensElement &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const LensElement &element);
};

struct CameraLensMetadata {
    CameraLensMetadata() = default;
    explicit CameraLensMetadata(const std::string &name);
    CameraLensMetadata(const std::string &name, float maximumAperture, float squeeze, const std::string &patent,
                       const std::string &description);
    std::string name;
    float maximumAperture;
    float squeeze;
    std::string patent;
    std::string description;

    bool operator==(const CameraLensMetadata &rhs) const;
    bool operator!=(const CameraLensMetadata &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const CameraLensMetadata &metadata);
};

struct CameraLens {
    CameraLens(const CameraLensMetadata &metadata, const std::vector<LensElement> &elements);
    CameraLens(const CameraLens &cameraLens);
    std::vector<LensElement> elements;
    ThickLensApproximation thickLensApproximation;
    float focalLength;

    CameraLensMetadata metadata;

    const LensElement &getFirstElement() const;
    const LensElement &getLastElement() const;
    LensElement &getAperture();
    float getApertureRadius() const;

    std::optional<Ray> traceFromFilmToWorld(const Ray &ray) const;
    std::optional<Ray> traceFromWorldToFilm(const Ray &ray) const;

    void focusLens(float focalDistance);
    void changeAperture(float fStop);

    Ray refract(const LensElementIntersection &intersection, const Ray &ray, float iorIn, float iorOut) const;
    bool operator==(const CameraLens &rhs) const;
    bool operator!=(const CameraLens &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const CameraLens &lens);

  private:
    std::optional<LensElementIntersection> intersect(const LensElement &element, const Ray &ray) const;
    bool exceedsAperture(const LensElement &element, const Ray &ray) const;
    bool exceedsAperture(const Vector3f &intersectionPosition, float apertureRadius) const;

    int apertureIndex = -1;
    float apertureRadius;
    float elementsOffset = 0;
};

} // crayg

template <> struct fmt::formatter<crayg::LensElement> : ostream_formatter {};

template <> struct fmt::formatter<crayg::CameraLensMetadata> : ostream_formatter {};

CRAYG_DTO_UTILS_VECTOR_FORMATTER(LensElement);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_
