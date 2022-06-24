#include "Transformable.h"

namespace crayg {

Transformable::Transformable() = default;

Transformable::Transformable(const Vector3f &position) :
    transform(Transform::withPosition(position)) {}

Vector3f Transformable::getPosition() const {
    return transform.toPosition();
}

void Transformable::setPosition(const Vector3f &position) {
    this->transform = Transform::withPosition(position);
}
const Transform Transformable::getTransform() const {
    return transform;
}
Transformable::Transformable(const Transform &transform) : transform(transform) {

}
void Transformable::setTransform(const Transform &transform) {
    Transformable::transform = transform;
}

}








