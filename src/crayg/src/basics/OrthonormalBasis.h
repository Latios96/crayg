#pragma once

#include "Vector3f.h"
#include "utils/ToStringHelper.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

class OrthonormalBasis {
  public:
    OrthonormalBasis(const Vector3f &normal) {
        v = normal;
        Vector3f a(0, 0, 1);
        float d = normal.dot(a);
        if (std::abs(d) > 0.50) {
            a = Vector3f(0, -1, 0);
        }
        u = normal.cross(a);
        w = u.cross(v);
    }

    OrthonormalBasis(const Vector3f &u, const Vector3f &v, const Vector3f &w) : u(u), v(v), w(w) {
    }

    Vector3f u, v, w;

    Vector3f toLocalCoordinates(const Vector3f &vec) const {
        return {u * vec.x + v * vec.y + w * vec.z};
    }

    bool operator==(const OrthonormalBasis &rhs) const;
    bool operator!=(const OrthonormalBasis &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const OrthonormalBasis &basis) {
        os << ToStringHelper("OrthonormalBasis")
                  .addMember("u", basis.u)
                  .addMember("v", basis.v)
                  .addMember("w", basis.w)
                  .finish();
        return os;
    }
};

} // crayg

template <> struct fmt::formatter<crayg::OrthonormalBasis> : ostream_formatter {};
