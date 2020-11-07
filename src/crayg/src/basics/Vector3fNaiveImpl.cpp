//
// Created by jan on 15.08.18.
//

#include <utils/ToStringHelper.h>
#include "Vector3fNaiveImpl.h"

Vector3fNaiveImpl::Vector3fNaiveImpl() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3fNaiveImpl::Vector3fNaiveImpl(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
}

Vector3fNaiveImpl Vector3fNaiveImpl::add(const Vector3fNaiveImpl &otherVector) const {
    return {x + otherVector.x, y + otherVector.y, z + otherVector.z};
}

Vector3fNaiveImpl Vector3fNaiveImpl::substract(const Vector3fNaiveImpl &otherVector) const {
    return {x - otherVector.x, y - otherVector.y, z - otherVector.z};
}

Vector3fNaiveImpl Vector3fNaiveImpl::multiplyScalar(float scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

float Vector3fNaiveImpl::length() const {
    return static_cast<float>(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
}

Vector3fNaiveImpl Vector3fNaiveImpl::normalize() const {
    float length = this->length();
    float oneByLength = 1 / length;

    return {x * oneByLength, y * oneByLength, z * oneByLength};
}

Vector3fNaiveImpl Vector3fNaiveImpl::crossProduct(const Vector3fNaiveImpl &otherVector) const {
    return {y * otherVector.z - otherVector.y * z,
            z * otherVector.x - otherVector.z * x,
            x * otherVector.y - otherVector.x * y};
}

Vector3fNaiveImpl Vector3fNaiveImpl::operator+(const Vector3fNaiveImpl &otherVector) const {
    return add(otherVector);
}

Vector3fNaiveImpl Vector3fNaiveImpl::operator-(const Vector3fNaiveImpl &otherVector) const {
    // return substract(otherVector);
    return {x - otherVector.x, y - otherVector.y, z - otherVector.z};
}

Vector3fNaiveImpl Vector3fNaiveImpl::operator*(float scalar) const {
    return multiplyScalar(scalar);
}

/*Vector3fNaiveImpl Vector3fNaiveImpl::operator*(const Vector3fNaiveImpl &otherVector) const {
    return crossProduct(otherVector);
}*/

float Vector3fNaiveImpl::scalarProduct(const Vector3fNaiveImpl &otherVector) const {
    return x * otherVector.x + y * otherVector.y + z * otherVector.z;
}

bool Vector3fNaiveImpl::operator==(const Vector3fNaiveImpl &otherVector) const {
    return this->x == otherVector.x && this->y == otherVector.y && this->z == otherVector.z;
}

bool Vector3fNaiveImpl::operator!=(const Vector3fNaiveImpl &otherVector) const {
    return !(this->x == otherVector.x && this->y == otherVector.y && this->z == otherVector.z);
}

Vector3fNaiveImpl Vector3fNaiveImpl::createInvalid() {
    auto max = std::numeric_limits<float>::max();
    return {max, max, max};
}

bool Vector3fNaiveImpl::isValid() {
    auto max = std::numeric_limits<float>::max();
    return x != max && y != max && z != max;
}

std::ostream &operator<<(std::ostream &os, const Vector3fNaiveImpl &f) {
    os << ToStringHelper("Vector3f")
            .addMember("x", f.x)
            .addMember("y", f.y)
            .addMember("z", f.z)
            .finish();
    return os;
}
