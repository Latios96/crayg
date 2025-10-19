#include "OrthonormalBasis.h"
#include "Vector3f_formatter.h"
#include "crayg/foundation/objects/ToStringHelper.h"

namespace crayg {

bool OrthonormalBasis::operator==(const OrthonormalBasis &rhs) const {
    return u == rhs.u && v == rhs.v && w == rhs.w;
}

bool OrthonormalBasis::operator!=(const OrthonormalBasis &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const OrthonormalBasis &basis) {
    os << ToStringHelper("OrthonormalBasis")
              .addMember("u", basis.u)
              .addMember("v", basis.v)
              .addMember("w", basis.w)
              .finish();
    return os;
}

}