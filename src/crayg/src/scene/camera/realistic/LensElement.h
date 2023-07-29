#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_LENSELEMENT_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_LENSELEMENT_H_

#include "LensGeometry.h"
#include "LensMaterial.h"
#include <fmt/ostream.h>

namespace crayg {

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

} // crayg

template <> struct fmt::formatter<crayg::LensElement> : ostream_formatter {};

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_LENSELEMENT_H_
