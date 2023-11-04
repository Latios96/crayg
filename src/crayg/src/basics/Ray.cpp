#include "Ray.h"
#include <limits>

namespace crayg {

std::ostream &operator<<(std::ostream &os, const Ray &ray) {
    os << "startPoint: " << ray.startPoint << " direction: " << ray.direction << " length: " << ray.length;
    return os;
}

}
