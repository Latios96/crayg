#include "OrthonormalBasis.h"

namespace crayg {

OrthonormalBasis::OrthonormalBasis(const Vector3f &u, const Vector3f &v, const Vector3f &w) : u(u), v(v), w(w) {}

Vector3f OrthonormalBasis::toLocalCoordinates(const Vector3f &vec) const {
    return {u * vec.x + v * vec.y + w * vec.z};
}
OrthonormalBasis::OrthonormalBasis(const Vector3f &normal) {
    w = normal;
    Vector3f a(0, 1, 0);
    float d = normal.dot(a);
    if (std::abs(d) <= 1) {
        a = Vector3f(1, 0, 0);
    }
    v = normal.cross(a);
    u = normal.cross(v);
}
bool OrthonormalBasis::operator==(const OrthonormalBasis &rhs) const {
    return u == rhs.u &&
        v == rhs.v &&
        w == rhs.w;
}
bool OrthonormalBasis::operator!=(const OrthonormalBasis &rhs) const {
    return !(rhs == *this);
}

} // crayg