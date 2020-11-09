//
// Created by jan on 22.08.18.
//

#include "Transformable.h"

Transformable::Transformable() : position(Vector3f()) {

}

Transformable::Transformable(Vector3f position) : position(position), transform(Transform::fromPosition(position)) {}

Vector3f Transformable::getPosition() const {
    return position;
}

void Transformable::setPosition(Vector3f position) {
    Transformable::position = position;
}







