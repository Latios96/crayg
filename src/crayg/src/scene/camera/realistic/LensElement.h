#pragma once

#include "LensGeometry.h"
#include "LensMaterial.h"
#include "basics/Ray.h"
#include "basics/Vector3f.h"
#include "utils/DtoUtils.h"
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

struct LensElement {
    LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius);
    LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius,
                std::optional<int> asphericCoefficientsIndex);
    LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber);
    LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
                std::optional<int> asphericCoefficientsIndex);
    LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
                LensMaterial lensMaterial, LensGeometry geometry);
    LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius, float abbeNumber,
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

    bool operator==(const LensElement &rhs) const;
    bool operator!=(const LensElement &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const LensElement &element);
};

bool intersectSphericalElement(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n);
bool intersectAsphericalElement(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n);
bool intersectCylindricalYElement(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n);
bool intersectCylindricalXElement(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n);
bool intersectPlanarElement(float zCenter, const Ray &ray, float *t, Vector3f *n);

} // crayg

template <> struct fmt::formatter<crayg::LensElement> : ostream_formatter {};

template <> struct fmt::formatter<crayg::AsphericCoefficients> : ostream_formatter {};

CRAYG_DTO_UTILS_VECTOR_FORMATTER(LensElement);
CRAYG_DTO_UTILS_VECTOR_FORMATTER(AsphericCoefficients);
