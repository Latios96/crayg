#include "LensElement.h"

#include "basics/MathUtils.h"
#include "utils/ToStringHelper.h"

namespace crayg {

LensElement::LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
                         LensMaterial lensMaterial, LensGeometry geometry)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior), apertureRadius(apertureRadius), center(0),
      abbeNumber(abbeNumber), material(lensMaterial), geometry(geometry) {
}

LensElement::LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior), apertureRadius(apertureRadius), center(0),
      abbeNumber(0), material(LensMaterial::UNKNOWN), geometry(LensGeometry::SPHERICAL) {
}

bool LensElement::isAperture() const {
    return curvatureRadius == 0;
}

inline Vector3f FaceForward(const Vector3f &n, const Vector3f &v) {
    return (n.dot(v) < 0.f) ? n.invert() : n;
}

float selectCorrectSolution(float radius, const Ray &ray, const QuadraticSolutions &quadraticSolutions) {
    auto [t0, t1] = quadraticSolutions;
    const bool isConcaveElement = radius < 0;
    const bool rayFromLeft = ray.direction.z > 0;
    bool useCloserT = rayFromLeft ^ isConcaveElement;

    if (useCloserT) {
        return std::min(t0, t1);
    }
    return std::max(t0, t1);
}

bool intersectSphericalElement(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n) {
    Vector3f o = ray.startPoint - Vector3f(0, 0, zCenter);
    float A = ray.direction.dot(ray.direction);
    float B = 2 * (ray.direction.dot(o));
    float C = o.dot(o) - radius * radius;

    auto solutions = MathUtils::solveQuadratic(A, B, C);
    if (!solutions) {
        return false;
    }

    *t = selectCorrectSolution(radius, ray, *solutions);
    if (*t < 0) {
        return false;
    }

    *n = Vector3f(o + ray.direction * *t);
    *n = FaceForward(n->normalize(), ray.direction.invert());

    return true;
}

bool LensElement::operator==(const LensElement &rhs) const {
    return curvatureRadius == rhs.curvatureRadius && thickness == rhs.thickness && ior == rhs.ior &&
           apertureRadius == rhs.apertureRadius && center == rhs.center && abbeNumber == rhs.abbeNumber &&
           material == rhs.material && geometry == rhs.geometry;
}

bool LensElement::operator!=(const LensElement &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const LensElement &element) {
    os << ToStringHelper("LensElement")
              .addMember("curvatureRadius", element.curvatureRadius)
              .addMember("thickness", element.thickness)
              .addMember("ior", element.ior)
              .addMember("apertureRadius", element.apertureRadius)
              .addMember("center", element.center)
              .addMember("abbeNumber", element.abbeNumber)
              .addMember("material", element.material)
              .addMember("geometry", element.geometry)
              .finish();
    return os;
}

} // crayg