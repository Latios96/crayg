//
// Created by jan on 22.08.18.
//

#include "Transformable.h"

Vector3f Transformable::getPosition() const {
    return position;
}

void Transformable::setPosition(Vector3f position) {
    Transformable::position = position;
}

Transformable::Transformable(Vector3f position) : position(position) {}





