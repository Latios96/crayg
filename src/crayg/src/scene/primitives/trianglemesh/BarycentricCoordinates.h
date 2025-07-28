#pragma once

#include "scene/primitives/trianglemesh/Triangle.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

class BarycentricCoordinates {
  public:
    BarycentricCoordinates(const Triangle &triangle, const Vector3f &point);
    BarycentricCoordinates(const Vector3f &v0, const Vector3f &v1, const Vector3f &v2, const Vector3f &normal,
                           const Vector3f &point);
    BarycentricCoordinates(float alpha, float beta, float gamma);

    bool operator==(const BarycentricCoordinates &rhs) const;
    bool operator!=(const BarycentricCoordinates &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const BarycentricCoordinates &coordinates);

    template <typename T> T interpolateLinear(const T &value1, const T &value2, const T &value3);

    float alpha, beta, gamma;
};

template <typename T> T BarycentricCoordinates::interpolateLinear(const T &value1, const T &value2, const T &value3) {
    return value1 * alpha + value2 * beta + value3 * gamma;
}

}

template <> struct fmt::formatter<crayg::BarycentricCoordinates> : ostream_formatter {};
