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

Vector3f Vector3f::add(const Vector3f &otherVector) const {
    return {x + otherVector.x, y + otherVector.y, z + otherVector.z};
}

Vector3f Vector3f::substract(const Vector3f &otherVector)const {
    return {x - otherVector.x, y - otherVector.y, z - otherVector.z};
}

Vector3f Vector3f::multiplyScalar(float scalar) const {
    return {x*scalar, y*scalar, z*scalar};
}

float Vector3f::length() const {
    return static_cast<float>(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
}

Vector3f Vector3f::normalize() const {
    float length = this->length();
    // TODO optimize with computing 1/length and multiply with vector components
    return {x / length, y / length, z / length};
}

Vector3f Vector3f::crossProduct(const Vector3f &otherVector) const {
    return {y * otherVector.z - otherVector.y * z,
            z * otherVector.x - otherVector.z * x,
            x * otherVector.y - otherVector.x * y};
}

Vector3f Vector3f::operator+(const Vector3f &otherVector) const {
    return add(otherVector);
}

Vector3f Vector3f::operator-(const Vector3f &otherVector) const {
    return substract(otherVector);
}

Vector3f Vector3f::operator*(float scalar) const {
    return multiplyScalar(scalar);
}

Vector3f Vector3f::operator*(const Vector3f &otherVector) const {
    return crossProduct(otherVector);
}

float Vector3f::scalarProduct(const Vector3f &otherVector) const {
    return x * otherVector.x + y * otherVector.y + z * otherVector.z;
}

bool Vector3f::operator==(const Vector3f &otherVector) const {
    return this->x == otherVector.x && this->y == otherVector.y && this->z == otherVector.z; 
}

bool Vector3f::operator!=(const Vector3f &otherVector) const {
    return !(this->x == otherVector.x && this->y == otherVector.y && this->z == otherVector.z);
}
