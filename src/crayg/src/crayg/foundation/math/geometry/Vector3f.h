#pragma once

#include "Vector2.h"
#include <cmath>
#include <limits>
#include <ostream>

namespace crayg {

class Vector3f {
  public:
    float x, y, z;

    Vector3f() {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3f(float x, float y, float z) : x(x), y(y), z(z) {
    }

    Vector3f operator+(const Vector3f &otherVector) const {
        return {x + otherVector.x, y + otherVector.y, z + otherVector.z};
    }

    Vector3f operator-(const Vector3f &otherVector) const {
        return {x - otherVector.x, y - otherVector.y, z - otherVector.z};
    }

    Vector3f operator+(float scalar) const {
        return {x + scalar, y + scalar, z + scalar};
    }

    Vector3f operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    Vector3f operator/(float scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }

    Vector3f &operator+=(const Vector3f &right) {
        x += right.x;
        y += right.y;
        z += right.z;
        return *this;
    }

    Vector3f &operator-=(const Vector3f &right) {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        return *this;
    }

    Vector3f &operator+=(float scalar) {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    Vector3f &operator-=(float scalar) {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }

    Vector3f &operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3f &operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    bool operator==(const Vector3f &otherVector) const {
        return this->x == otherVector.x && this->y == otherVector.y && this->z == otherVector.z;
    }

    bool operator!=(const Vector3f &otherVector) const {
        return !(this->x == otherVector.x && this->y == otherVector.y && this->z == otherVector.z);
    }

    float dot(const Vector3f &otherVector) const {
        return x * otherVector.x + y * otherVector.y + z * otherVector.z;
    }

    float length() const {
        return static_cast<float>(sqrt(x * x + y * y + z * z));
    }

    float lengthSquared() const {
        return static_cast<float>(x * x + y * y + z * z);
    }

    Vector3f normalize() const {
        float length = this->length();
        float oneByLength = 1 / length;

        return {x * oneByLength, y * oneByLength, z * oneByLength};
    }

    Vector3f invert() const {
        return {x * -1, y * -1, z * -1};
    }

    Vector3f cross(const Vector3f &otherVector) const {
        return {y * otherVector.z - otherVector.y * z, z * otherVector.x - otherVector.z * x,
                x * otherVector.y - otherVector.x * y};
    }

    Vector3f reflect(const Vector3f &normal) const {
        return (*this) - (normal * 2 * (this->dot(normal)));
    }

    static Vector3f createInvalid() {
        auto max = std::numeric_limits<float>::max();
        return {max, max, max};
    }

    bool isValid() const {
        auto max = std::numeric_limits<float>::max();
        return x != max && y != max && z != max;
    }

    Vector2f xy() const {
        return {x, y};
    }

    Vector2f xz() const {
        return {x, z};
    }

    Vector2f yz() const {
        return {y, z};
    }

    bool hasNaN() const {
        return std::isnan(x) || std::isnan(y) || std::isnan(z);
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector3f &f);
};

}
