#include "Imageable.h"

#include <utility>

namespace crayg {

Imageable::Intersection::Intersection(float rayParameter, Imageable *imageable) : rayParameter(
    rayParameter), imageable(imageable) {}

Imageable::Intersection Imageable::Intersection::nearest(const Imageable::Intersection &first,
                                                         const Imageable::Intersection &second) {
    if (first.rayParameter < second.rayParameter && first.imageable && first.rayParameter > 0) {
        return first;
    }
    return second;
}
Imageable::Intersection::Intersection(float rayParameter, Imageable *imageable, bool isOwning) : rayParameter(
    rayParameter), imageable(imageable), isOwning(isOwning) {

}
Imageable::Intersection::~Intersection() {
    if (isOwning) {
        delete imageable;
    }
}
std::shared_ptr<Material> Imageable::getMaterial() const {
    return material;
}
void Imageable::setMaterial(const std::shared_ptr<Material> &material) {
    Imageable::material = material;
}
OrthonormalBasis Imageable::getOrthonormalBasis(const Vector3f &point) {
    return OrthonormalBasis(getNormal(point));
}

}