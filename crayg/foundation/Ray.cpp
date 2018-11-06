//
// Created by jan on 16.08.18.
//

#include <limits>
#include "Ray.h"

Ray::Ray(Vector3f startPoint, Vector3f direction){
    this->startPoint = startPoint;
    this->direction = direction;
    this->length = std::numeric_limits<float>::min();
}

Ray::Ray(Vector3f startPoint, Vector3f direction, float length){
    this->startPoint = startPoint;
    this->direction = direction;
    this->length = length;
}

Ray Ray::createInvalid() {
    return {Vector3f::createInvalid(), Vector3f::createInvalid(), std::numeric_limits<float>::max()};
}

bool Ray::isValid() {
    return startPoint.isValid() && direction.isValid() && length != std::numeric_limits<float>::max();
}


