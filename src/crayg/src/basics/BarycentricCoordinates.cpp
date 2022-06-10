//
// Created by Jan on 10.06.2022.
//

#include "BarycentricCoordinates.h"
#include "utils/ToStringHelper.h"

namespace crayg {

BarycentricCoordinates::BarycentricCoordinates(float alpha, float beta, float gamma)
    : alpha(alpha), beta(beta), gamma(gamma) {}

BarycentricCoordinates::BarycentricCoordinates(const Triangle &triangle, const Vector3f &point)
    : BarycentricCoordinates(triangle.v0(), triangle.v1(), triangle.v2(), triangle.getNormal(), point) {
}

BarycentricCoordinates::BarycentricCoordinates(const Vector3f &v0,
                                               const Vector3f &v1,
                                               const Vector3f &v2,
                                               const Vector3f &normal,
                                               const Vector3f &point) {
// based on Fundamentals of Computer Graphics, 2016, p. 49
    float lengthSquared = normal.lengthSquared();
    alpha = normal.scalarProduct((v2 - v1).crossProduct(point - v1)) / lengthSquared;
    beta = normal.scalarProduct((v0 - v2).crossProduct(point - v2)) / lengthSquared;
    gamma = normal.scalarProduct((v1 - v0).crossProduct(point - v0)) / lengthSquared;
}
bool BarycentricCoordinates::operator==(const BarycentricCoordinates &rhs) const {
    return alpha == rhs.alpha &&
        beta == rhs.beta &&
        gamma == rhs.gamma;
}
bool BarycentricCoordinates::operator!=(const BarycentricCoordinates &rhs) const {
    return !(rhs == *this);
}
std::ostream &operator<<(std::ostream &os, const BarycentricCoordinates &coordinates) {
    os << ToStringHelper("BarycentricCoordinates")
        .addMember("alpha", coordinates.alpha)
        .addMember("beta", coordinates.beta)
        .addMember("gamma", coordinates.gamma)
        .finish();
    return os;
}

} // crayg