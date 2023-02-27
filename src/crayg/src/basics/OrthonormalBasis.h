#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_ORTHONORMALBASIS_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_ORTHONORMALBASIS_H_

#include "Vector3f.h"
#include "utils/ToStringHelper.h"
#include <ostream>

namespace crayg {

class OrthonormalBasis {
  public:
    OrthonormalBasis(const Vector3f &normal);
    OrthonormalBasis(const Vector3f &u, const Vector3f &v, const Vector3f &w);
    Vector3f u, v, w;

    Vector3f toLocalCoordinates(const Vector3f &vec) const;

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

#endif // CRAYG_SRC_CRAYG_SRC_BASICS_ORTHONORMALBASIS_H_
