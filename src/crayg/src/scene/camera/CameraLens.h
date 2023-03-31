#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_

#include "basics/Ray.h"
#include "utils/DtoUtils.h"
#include <optional>
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
};

struct CameraLens {
    CameraLens(const std::string &name, const std::vector<LensElement> &elements);
    std::string name;
    std::vector<LensElement> elements;

    const LensElement &getFirstElement() const;
    const LensElement &getLastElement() const;

    Ray traceFromFilmToWorld(const Ray &ray) const;
    Ray traceFromWorldToFilm(const Ray &ray) const;

  private:
    Ray refract(const LensElementIntersection &intersection, const Ray &ray, float iorIn, float iorOut) const;
    float getNextIor(int currentIndex, int indexOffset) const;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERALENS_H_
