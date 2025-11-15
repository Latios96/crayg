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

CRAYG_TO_STRING_HELPER_OSTREAM_IMPL(OrthonormalBasis, u, v, w);

}