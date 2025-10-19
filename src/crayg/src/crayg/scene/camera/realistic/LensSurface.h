#pragma once

#include "LensGeometry.h"
#include "LensMaterial.h"
#include "crayg/foundation/math/geometry/Ray.h"
#include "crayg/foundation/math/geometry/Vector3f.h"
#include "crayg/foundation/objects/DtoUtils.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

struct AsphericCoefficients {
    float k = 0;
    float a2 = 0;
    float a4 = 0;
    float a6 = 0;
    float a8 = 0;
    float a10 = 0;
    float a12 = 0;
    float a14 = 0;
    bool operator==(const AsphericCoefficients &rhs) const;
    bool operator!=(const AsphericCoefficients &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const AsphericCoefficients &coefficients);
};

struct LensSurface {
    LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius);
    LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius,
                std::optional<int> asphericCoefficientsIndex);
    LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber);
    LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
                std::optional<int> asphericCoefficientsIndex);
    LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
                LensMaterial lensMaterial, LensGeometry geometry);
    LensSurface(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
                LensMaterial lensMaterial, LensGeometry geometry, std::optional<int> asphericCoefficientsIndex);

    float curvatureRadius;
    float thickness;
    float ior;
    float apertureRadius;
    float center;
    float abbeNumber;
    LensMaterial material;
    LensGeometry geometry;
    std::optional<int> asphericCoefficientsIndex;

    bool isAperture() const;

    LensSurface scaled(float scaleToApply) {
        LensSurface surface = *this;
        surface.curvatureRadius *= scaleToApply;
        surface.thickness *= scaleToApply;
        surface.apertureRadius *= scaleToApply;
        return surface;
    }

    bool operator==(const LensSurface &rhs) const;
    bool operator!=(const LensSurface &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const LensSurface &surface);
};

bool intersectSphericalSurface(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n);
bool intersectAsphericalSurface(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n,
                                const AsphericCoefficients &asphericCoefficients);
bool intersectCylindricalYSurface(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n);
bool intersectCylindricalXSurface(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n);
bool intersectPlanarSurface(float zCenter, const Ray &ray, float *t, Vector3f *n);

float evaluateAsphericalSurface(const Vector2f &position, float radius,
                                const AsphericCoefficients &asphericCoefficients);

}

template <> struct fmt::formatter<crayg::LensSurface> : ostream_formatter {};

template <> struct fmt::formatter<crayg::AsphericCoefficients> : ostream_formatter {};
