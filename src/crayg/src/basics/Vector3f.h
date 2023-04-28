#ifndef CRAYG_VECTOR3F_H
#define CRAYG_VECTOR3F_H

#include "Vector2.h"
#include <cmath>
#include <fmt/ostream.h>
#include <limits>
#include <ostream>

namespace crayg {

class Vector3f {
  public:
    float x, y, z;

    Vector3f();

    Vector3f(float x, float y, float z);

    Vector3f operator+(const Vector3f &otherVector) const;

    Vector3f operator-(const Vector3f &otherVector) const;

    Vector3f operator+(float scalar) const;

    Vector3f operator*(float scalar) const;

    Vector3f operator/(float scalar) const;

    Vector3f &operator+=(const Vector3f &right);

    Vector3f &operator-=(const Vector3f &right);

    Vector3f &operator+=(float scalar);

    Vector3f &operator-=(float scalar);

    Vector3f &operator*=(float scalar);

    Vector3f &operator/=(float scalar);

    bool operator==(const Vector3f &otherVector) const;

    bool operator!=(const Vector3f &otherVector) const;

    float dot(const Vector3f &otherVector) const;

    float length() const;

    float lengthSquared() const;

    Vector3f normalize() const;

    Vector3f invert() const;

    Vector3f cross(const Vector3f &otherVector) const;

    Vector3f reflect(const Vector3f &normal) const;

    static Vector3f createInvalid();

    bool isValid() const;

    Vector2f xy() const;

    Vector2f xz() const;

    Vector2f yz() const;

    friend std::ostream &operator<<(std::ostream &os, const Vector3f &f);
};

}

template <> struct fmt::formatter<crayg::Vector3f> : ostream_formatter {};

#endif // CRAYG_VECTOR3F_H
