#include "OrthonormalBasis.h"

namespace crayg {

OrthonormalBasis::OrthonormalBasis(const Vector3f &u, const Vector3f &v, const Vector3f &w) : u(u), v(v), w(w) {
}

Vector3f OrthonormalBasis::toLocalCoordinates(const Vector3f &vec) const {
    return {u * vec.x + v * vec.y + w * vec.z};
}

OrthonormalBasis::OrthonormalBasis(const Vector3f &normal) {
    v = normal;
    Vector3f a(0, 0, 1);
    float d = normal.dot(a);
    if (std::abs(d) > 0.50) {
        a = Vector3f(0, -1, 0);
    }
    u = normal.cross(a);
    w = u.cross(v);
}

bool OrthonormalBasis::operator==(const OrthonormalBasis &rhs) const {
    return u == rhs.u && v == rhs.v && w == rhs.w;
}

bool OrthonormalBasis::operator!=(const OrthonormalBasis &rhs) const {
    return !(rhs == *this);
}

} // crayg