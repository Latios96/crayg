//
// Created by jan on 22.08.18.
//

#include "Transformable.h"

Transformable::Transformable() = default;

Transformable::Transformable(const Vector3f &position) :
    transform(Transform::fromPosition(position)) {}

Vector3f Transformable::getPosition() const {
    return transform.toPosition();
}

void Transformable::setPosition(const Vector3f &position) {
    this->transform = Transform::fromPosition(position);
}








