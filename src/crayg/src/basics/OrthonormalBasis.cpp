#include "OrthonormalBasis.h"

namespace crayg {

bool OrthonormalBasis::operator==(const OrthonormalBasis &rhs) const {
    return u == rhs.u && v == rhs.v && w == rhs.w;
}

bool OrthonormalBasis::operator!=(const OrthonormalBasis &rhs) const {
    return !(rhs == *this);
}

}