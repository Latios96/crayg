#include "Transformable.h"

namespace crayg {

Transformable::Transformable() = default;

Transformable::Transformable(const Vector3f &position) : transform(Transform::withPosition(position)) {
}

void Transformable::setPosition(const Vector3f &position) {
    this->transform = Transform::withPosition(position);
}

Transformable::Transformable(const Transform &transform) : transform(transform) {
}

void Transformable::setTransform(const Transform &transform) {
    Transformable::transform = transform;
}

}
