//
// Created by jan on 15.08.18.
//

#ifndef CRAYG_VECTOR3F_H
#define CRAYG_VECTOR3F_H

#include <cmath>
#include <limits>
#include <ostream>

class Vector3f {
 public:
    float x, y, z;

    /**
    Creates a new Vector and initialised x,y,z to 0
    */
    Vector3f();

    Vector3f(float _x, float _y, float _z);

    Vector3f operator+(const Vector3f &otherVector) const;

    Vector3f operator-(const Vector3f &otherVector) const;

    Vector3f operator*(float scalar) const;

    Vector3f operator*(const Vector3f &otherVector) const;

    bool operator==(const Vector3f &otherVector) const;

    bool operator!=(const Vector3f &otherVector) const;

    Vector3f add(const Vector3f &otherVector) const;

    Vector3f substract(const Vector3f &otherVector) const;

    Vector3f multiplyScalar(float scalar) const;

    float scalarProduct(const Vector3f &otherVector) const;

    float length() const;

    Vector3f normalize() const;

    Vector3f invert() const {
        return {x * -1, y * -1, z * -1};
    }

    Vector3f crossProduct(const Vector3f &otherVector) const;

    static Vector3f createInvalid();

    bool isValid();

    friend std::ostream &operator<<(std::ostream &os, const Vector3f &f);

};

#endif //CRAYG_VECTOR3F_H
