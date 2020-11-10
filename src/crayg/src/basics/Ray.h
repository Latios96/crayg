//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_RAY_H
#define CRAYG_RAY_H

#include <ostream>
#include "Vector3f.h"

struct Ray {
    Vector3f startPoint, direction;
    float length;
 public:
    Ray(Vector3f startPoint, Vector3f direction);

    Ray(Vector3f startPoint, Vector3f direction, float length);

    static Ray createInvalid();

    bool isValid();

    Vector3f constructIntersectionPoint() const;

    Vector3f constructIntersectionPoint(float t) const;
    bool operator==(const Ray &rhs) const;
    bool operator!=(const Ray &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);
};

#endif //CRAYG_RAY_H
