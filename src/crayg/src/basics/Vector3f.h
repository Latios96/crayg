#ifndef CRAYG_VECTOR3F_H
#define CRAYG_VECTOR3F_H

#include <cmath>
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

    Vector3f operator*(float scalar) const;

    Vector3f operator/(float scalar) const;

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

    friend std::ostream &operator<<(std::ostream &os, const Vector3f &f);
};

}
#endif // CRAYG_VECTOR3F_H
