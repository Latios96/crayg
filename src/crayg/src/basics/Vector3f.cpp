#include "Vector3f.h"
#include <utils/ToStringHelper.h>

namespace crayg {
std::ostream &operator<<(std::ostream &os, const Vector3f &f) {
    os << ToStringHelper("Vector3f").addMember("x", f.x).addMember("y", f.y).addMember("z", f.z).finish();
    return os;
}
}
