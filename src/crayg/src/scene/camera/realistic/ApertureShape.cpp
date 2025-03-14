#include "ApertureShape.h"

#include "basics/Transform.h"
#include "sampling/Sampling.h"

#include <boost/math/constants/constants.hpp>

namespace crayg {

float ApertureShape::getRadius() const {
    return radius;
}

std::optional<int> ApertureShape::getSides() const {
    return sides;
}

void ApertureShape::setRadius(float radius) {
    this->radius = radius;
    buildPolygons();
}

void ApertureShape::setSides(const std::optional<int> &sides) {
    this->sides = sides;
    buildPolygons();
}

bool ApertureShape::isRoundAperture() const {
    return sides.has_value();
}

Vector2f ApertureShape::samplePoint() const {
    if (isRoundAperture()) {
        return Sampling::concentricSampleDisk() * radius;
    }

    // find corresponding polygon

    // map to point in triangle
}

bool ApertureShape::pointExceedsAperture(const Vector2f &point) {
    const bool exceededsRoundAperture = point.lengthSquared() > radius * radius;
    if (exceededsRoundAperture || isRoundAperture()) {
        return exceededsRoundAperture;
    }

    // find corresponding polygon
    // check if point lies right or left to line
    // determine result
}

void ApertureShape::buildPolygons() {
    if (!sides) {
        return;
    }
    bladePolygons.resize(*sides);

    Vector2f pointOnBorder(0, radius);
    const float stepSize = boost::math::constants::two_pi<float>() / static_cast<float>(*sides);

    for (int i = 0; i < *sides; i++) {
        const float angle = stepSize * i;
        bladePolygons[i].x = pointOnBorder.x * cos(angle) - pointOnBorder.y * sin(angle);
        bladePolygons[i].y = pointOnBorder.x * sin(angle) + pointOnBorder.y * cos(angle);
    }
}
}