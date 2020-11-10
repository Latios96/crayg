//
// Created by jan on 22.08.18.
//

#include "Transformable.h"

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








