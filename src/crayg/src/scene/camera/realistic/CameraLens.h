#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_

#include "CameraLensMetadata.h"
#include "LensElement.h"
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

struct CameraLens {
    CameraLens(const CameraLensMetadata &metadata, const std::vector<LensElement> &elements);
    CameraLens(const CameraLens &cameraLens);
    std::vector<LensElement> elements;
    ThickLensApproximation thickLensApproximation;

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

CRAYG_DTO_UTILS_VECTOR_FORMATTER(LensElement);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_
