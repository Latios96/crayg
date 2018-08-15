//
// Created by jan on 15.08.18.
//

#include "Vector3f.h"

Vector3f::Vector3f()  {
    x = 0;
    y = 0;
    z = 0;
}

Vector3f::Vector3f(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
}

Vector3f Vector3f::add(const Vector3f &otherVector) {
    return {x + otherVector.x, y + otherVector.y, z + otherVector.z};
}

Vector3f Vector3f::substract(const Vector3f &otherVector) {
    return {x - otherVector.x, y - otherVector.y, z - otherVector.z};
}

Vector3f Vector3f::multiplyScalar(float scalar) {
    return {x*scalar, y*scalar, z*scalar};
}

float Vector3f::length() {
    return static_cast<float>(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
}

Vector3f Vector3f::normalize() {
    float length = this->length();
    // TODO optimize with computing 1/length and multiply with vector components
    return {x / length, y / length, z / length};
}

Vector3f Vector3f::crossProduct(const Vector3f &otherVector) {
    return {y * otherVector.z - otherVector.y * z,
            z * otherVector.x - otherVector.z * x,
            x * otherVector.y - otherVector.x * y};
}