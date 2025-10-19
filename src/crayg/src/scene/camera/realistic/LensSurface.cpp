#include "LensSurface.h"

#include "crayg/foundation/math/QuadraticEquations.h"
#include "crayg/foundation/objects/ToStringHelper.h"
#include <cmath>

namespace crayg {

LensSurface::LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
                         LensMaterial lensMaterial, LensGeometry geometry)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior), apertureRadius(apertureRadius), center(0),
      abbeNumber(abbeNumber), material(lensMaterial), geometry(geometry), asphericCoefficientsIndex(std::nullopt) {
}

LensSurface::LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
                         LensMaterial lensMaterial, LensGeometry geometry, std::optional<int> asphericCoefficientsIndex)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior), apertureRadius(apertureRadius), center(0),
      abbeNumber(abbeNumber), material(lensMaterial), geometry(geometry),
      asphericCoefficientsIndex(asphericCoefficientsIndex) {
}

LensSurface::LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior), apertureRadius(apertureRadius), center(0),
      abbeNumber(0), material(LensMaterial()), geometry(LensGeometry::SPHERICAL),
      asphericCoefficientsIndex(std::nullopt) {
}

LensSurface::LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius,
                         std::optional<int> asphericCoefficientsIndex)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior), apertureRadius(apertureRadius), center(0),
      abbeNumber(0), material(LensMaterial()), geometry(LensGeometry::SPHERICAL),
      asphericCoefficientsIndex(asphericCoefficientsIndex) {
}

LensSurface::LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior), apertureRadius(apertureRadius), center(0),
      abbeNumber(abbeNumber), material(LensMaterial()), geometry(LensGeometry::SPHERICAL),
      asphericCoefficientsIndex(std::nullopt) {
}

LensSurface::LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
                         std::optional<int> asphericCoefficientsIndex)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior), apertureRadius(apertureRadius), center(0),
      abbeNumber(abbeNumber), material(LensMaterial()), geometry(LensGeometry::SPHERICAL),
      asphericCoefficientsIndex(asphericCoefficientsIndex) {
}

bool LensSurface::isAperture() const {
    return curvatureRadius == 0;
}

inline Vector3f FaceForward(const Vector3f &n, const Vector3f &v) {
    return (n.dot(v) < 0.f) ? n.invert() : n;
}

float selectCorrectSolution(float radius, const Ray &ray, const QuadraticSolutions &quadraticSolutions) {
    auto [t0, t1] = quadraticSolutions;
    const bool isConcaveSurface = radius < 0;
    const bool rayFromLeft = ray.direction.z > 0;
    bool useCloserT = rayFromLeft ^ isConcaveSurface;

    if (useCloserT) {
        return std::min(t0, t1);
    }
    return std::max(t0, t1);
}

bool intersectSphericalSurface(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n) {
    Vector3f o = ray.startPoint - Vector3f(0, 0, zCenter);
    float A = ray.direction.dot(ray.direction);
    float B = 2 * (ray.direction.dot(o));
    float C = o.dot(o) - radius * radius;

    auto solutions = QuadraticEquations::solveQuadratic(A, B, C);
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

float evaluateAsphericalSurface(const Vector2f &position, float radius,
                                const AsphericCoefficients &asphericCoefficients) {
    const float h = position.length();
    const float h2 = h * h;
    const float h4 = h2 * h2;
    const float h6 = h4 * h2;
    const float h8 = h4 * h4;
    const float h10 = h8 * h2;
    const float h12 = h10 * h2;
    const float h14 = h12 * h2;
    float curvature = 1.f / radius;
    const float sumOfCorrectionTerms = asphericCoefficients.a2 * h2 + asphericCoefficients.a4 * h4 +
                                       asphericCoefficients.a6 * h6 + asphericCoefficients.a8 * h8 +
                                       asphericCoefficients.a10 * h10 + asphericCoefficients.a12 * h12 +
                                       asphericCoefficients.a14 * h14;
    return (curvature * h2) /
               (1 + std::sqrt(std::max(0.f, 1 - (1 + asphericCoefficients.k) * curvature * curvature * h2))) +
           sumOfCorrectionTerms;
}

float evaluateAsphericalSurfaceDerivate(const Vector2f &position, float radius,
                                        const AsphericCoefficients &asphericCoefficients) {
    const float h = position.length();
    const float h2 = h * h;
    const float h3 = h2 * h;
    const float h5 = h3 * h2;
    const float h7 = h5 * h2;
    const float h9 = h7 * h2;
    const float h11 = h9 * h2;
    const float h13 = h11 * h2;
    float curvature = 1.f / radius;
    float curvature2 = curvature * curvature;

    const float sumOfCorrectionTerms = 2 * asphericCoefficients.a2 * h + 4 * asphericCoefficients.a4 * h3 +
                                       6 * asphericCoefficients.a6 * h5 + 8 * asphericCoefficients.a8 * h7 +
                                       10 * asphericCoefficients.a10 * h9 + 12 * asphericCoefficients.a12 * h11 +
                                       14 * asphericCoefficients.a14 * h13;

    return (2.f * curvature * h) / (std::sqrt(1 - curvature2 * h2 * (asphericCoefficients.k + 1)) + 1) +
           (curvature2 * curvature * h3 * (asphericCoefficients.k + 1)) /
               (std::sqrt(1 - curvature2 * h2 * (asphericCoefficients.k + 1)) *
                std::pow(std::sqrt(1 - curvature2 * h2 * (asphericCoefficients.k + 1)) + 1, 2)) +
           sumOfCorrectionTerms;
}

bool intersectAsphericalSurface(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n,
                                const AsphericCoefficients &asphericCoefficients) {
    if (!intersectSphericalSurface(radius, zCenter, ray, t, n)) {
        return false;
    }
    Vector3f intersectionPointWithAsphere = ray.constructIntersectionPoint(*t);
    float asphericSagitta = evaluateAsphericalSurface(intersectionPointWithAsphere.xy(), radius, asphericCoefficients);

    float positionError = 1e10;
    for (int i = 0; i < 100; i++) {
        positionError = zCenter + asphericSagitta - intersectionPointWithAsphere.z;
        float tError = positionError / ray.direction.z;
        *t = +tError;
        intersectionPointWithAsphere = ray.constructIntersectionPoint(*t);
        if (std::abs(positionError) < 1e-4) {
            break;
        }
    };

    float dz = evaluateAsphericalSurfaceDerivate(intersectionPointWithAsphere.xy(), radius, asphericCoefficients);
    const float r = intersectionPointWithAsphere.xy().length();

    if (n->z > 0) {
        dz = -dz;
    }
    Vector3f normal(intersectionPointWithAsphere.x / r * dz, intersectionPointWithAsphere.y / r * dz,
                    n->z / std::abs(n->z));
    *n = normal.normalize();

    return true;
}

bool intersectCylindricalYSurface(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n) {
    const Vector3f transformedOrigin = ray.startPoint - Vector3f(0, 0, zCenter);
    const float A = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    const float B = 2 * (ray.direction.x * transformedOrigin.x + ray.direction.z * transformedOrigin.z);
    const float C =
        transformedOrigin.x * transformedOrigin.x + transformedOrigin.z * transformedOrigin.z - radius * radius;

    auto solutions = QuadraticEquations::solveQuadratic(A, B, C);
    if (!solutions) {
        return false;
    }

    *t = selectCorrectSolution(radius, ray, *solutions);
    if (*t < 0) {
        return false;
    }

    const auto posOnCylinder = Vector3f(transformedOrigin + ray.direction * *t);
    n->x = posOnCylinder.x / radius;
    n->y = 0;
    n->z = posOnCylinder.z / radius;
    *n = FaceForward(*n, ray.direction * -1);

    return true;
}

bool intersectCylindricalXSurface(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n) {
    Vector3f transformedOrigin = ray.startPoint - Vector3f(0, 0, zCenter);
    const float A = ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z;
    const float B = 2 * (ray.direction.y * transformedOrigin.y + ray.direction.z * transformedOrigin.z);
    const float C =
        transformedOrigin.y * transformedOrigin.y + transformedOrigin.z * transformedOrigin.z - radius * radius;

    auto solutions = QuadraticEquations::solveQuadratic(A, B, C);
    if (!solutions) {
        return false;
    }

    *t = selectCorrectSolution(radius, ray, *solutions);
    if (*t < 0) {
        return false;
    }

    const auto posOnCylinder = Vector3f(transformedOrigin + ray.direction * *t);
    n->x = 0;
    n->y = posOnCylinder.y / radius;
    n->z = posOnCylinder.z / radius;
    *n = FaceForward(*n, ray.direction * -1);

    return true;
}

bool intersectPlanarSurface(float zCenter, const Ray &ray, float *t, Vector3f *n) {
    *t = zCenter / ray.direction.z;
    *n = Vector3f(0, 0, -1);
    *n = *n = FaceForward(*n, ray.direction * -1);
    return true;
}

bool LensSurface::operator==(const LensSurface &rhs) const {
    return curvatureRadius == rhs.curvatureRadius && thickness == rhs.thickness && ior == rhs.ior &&
           apertureRadius == rhs.apertureRadius && center == rhs.center && abbeNumber == rhs.abbeNumber &&
           material == rhs.material && geometry == rhs.geometry &&
           asphericCoefficientsIndex == rhs.asphericCoefficientsIndex;
}

bool LensSurface::operator!=(const LensSurface &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const LensSurface &surface) {
    os << ToStringHelper("LensSurface")
              .addMember("curvatureRadius", surface.curvatureRadius)
              .addMember("thickness", surface.thickness)
              .addMember("ior", surface.ior)
              .addMember("apertureRadius", surface.apertureRadius)
              .addMember("center", surface.center)
              .addMember("abbeNumber", surface.abbeNumber)
              .addMember("material", surface.material)
              .addMember("geometry", surface.geometry)
              .finish();
    return os;
}

std::ostream &operator<<(std::ostream &os, const AsphericCoefficients &coefficients) {
    os << ToStringHelper("AsphericCoefficients")
              .addMember("k", coefficients.k)
              .addMember("a2", coefficients.a2)
              .addMember("a4", coefficients.a4)
              .addMember("a6", coefficients.a6)
              .addMember("a8", coefficients.a8)
              .addMember("a10", coefficients.a10)
              .addMember("a12", coefficients.a12)
              .addMember("a14", coefficients.a14)
              .finish();
    return os;
}

bool AsphericCoefficients::operator==(const AsphericCoefficients &rhs) const {
    return k == rhs.k && a2 == rhs.a2 && a4 == rhs.a4 && a6 == rhs.a6 && a8 == rhs.a8 && a10 == rhs.a10 &&
           a12 == rhs.a12 && a14 == rhs.a14;
}

bool AsphericCoefficients::operator!=(const AsphericCoefficients &rhs) const {
    return !(rhs == *this);
}
}