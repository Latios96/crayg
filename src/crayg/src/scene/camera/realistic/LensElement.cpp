#include "LensElement.h"
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