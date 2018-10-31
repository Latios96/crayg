//
// Created by jan on 16.08.18.
//

#include <limits>
#include "Ray.h"
// todo implement ==, !=
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


