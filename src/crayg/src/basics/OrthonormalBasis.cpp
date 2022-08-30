#include "OrthonormalBasis.h"

namespace crayg {

OrthonormalBasis::OrthonormalBasis(const Vector3f &u, const Vector3f &v, const Vector3f &w) : u(u), v(v), w(w) {}

Vector3f OrthonormalBasis::toLocalCoordinates(const Vector3f &vec) const {
    return {u * vec.x + v * vec.y + w * vec.z};
}

} // crayg