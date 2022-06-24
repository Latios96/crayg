#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_BARYCENTRICCOORDINATES_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_BARYCENTRICCOORDINATES_H_

#include <ostream>
#include "scene/trianglemesh/Triangle.h"

namespace crayg {

class BarycentricCoordinates {
 public:
    BarycentricCoordinates(const Triangle &triangle, const Vector3f &point);
    BarycentricCoordinates(const Vector3f &v0,
                           const Vector3f &v1,
                           const Vector3f &v2,
                           const Vector3f &normal,
                           const Vector3f &point);
    BarycentricCoordinates(float alpha, float beta, float gamma);

    bool operator==(const BarycentricCoordinates &rhs) const;
    bool operator!=(const BarycentricCoordinates &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const BarycentricCoordinates &coordinates);

    template<typename T>
    T interpolateLinear(const T &value1, const T &value2, const T &value3);

    float alpha, beta, gamma;
};

template<typename T>
T BarycentricCoordinates::interpolateLinear(const T &value1,
                                            const T &value2,
                                            const T &value3) {
    return value1 * alpha + value2 * beta + value3 * gamma;
}

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_BASICS_BARYCENTRICCOORDINATES_H_
