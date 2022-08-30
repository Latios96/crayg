#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_ORTHONORMALBASIS_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_ORTHONORMALBASIS_H_

#include "Vector3f.h"
namespace crayg {

class OrthonormalBasis {
 public:
    OrthonormalBasis(const Vector3f &u, const Vector3f &v, const Vector3f &w);
    const Vector3f u, v, w;

    Vector3f toLocalCoordinates(const Vector3f &vec) const;

};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_BASICS_ORTHONORMALBASIS_H_
