//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_RAY_H
#define CRAYG_RAY_H

#include "Vector3f.h"
// todo implement ==, !=
struct Ray {
    Vector3f startPoint, direction;
    float length;
 public:
    Ray(Vector3f startPoint, Vector3f direction);

    Ray(Vector3f startPoint, Vector3f direction, float length);

    static Ray createInvalid();

    bool isValid();

    Vector3f constructIntersectionPoint();

    Vector3f constructIntersectionPoint(float t);

};

#endif //CRAYG_RAY_H