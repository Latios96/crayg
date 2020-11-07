//
// Created by Jan on 07.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_Vector3fNaiveImpl_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_Vector3fNaiveImpl_H_

#include <cmath>
#include <limits>
#include <ostream>

class Vector3fNaiveImpl {
 public:
    float x, y, z;

    /**
    Creates a new Vector and initialised x,y,z to 0
    */
    Vector3fNaiveImpl();

    Vector3fNaiveImpl(float _x, float _y, float _z);

    Vector3fNaiveImpl operator+(const Vector3fNaiveImpl &otherVector) const;

    Vector3fNaiveImpl operator-(const Vector3fNaiveImpl &otherVector) const;

    Vector3fNaiveImpl operator*(float scalar) const;

    Vector3fNaiveImpl operator*(const Vector3fNaiveImpl &otherVector) const;

    bool operator==(const Vector3fNaiveImpl &otherVector) const;

    bool operator!=(const Vector3fNaiveImpl &otherVector) const;

    Vector3fNaiveImpl add(const Vector3fNaiveImpl &otherVector) const;

    Vector3fNaiveImpl substract(const Vector3fNaiveImpl &otherVector) const;

    Vector3fNaiveImpl multiplyScalar(float scalar) const;

    float scalarProduct(const Vector3fNaiveImpl &otherVector) const;

    float length() const;

    Vector3fNaiveImpl normalize() const;

    Vector3fNaiveImpl invert() const {
        return {x * -1, y * -1, z * -1};
    }

    Vector3fNaiveImpl crossProduct(const Vector3fNaiveImpl &otherVector) const;

    static Vector3fNaiveImpl createInvalid();

    bool isValid();

    friend std::ostream &operator<<(std::ostream &os, const Vector3fNaiveImpl &f);

};

#endif //CRAYG_SRC_CRAYG_SRC_BASICS_Vector3fNaiveImpl_H_
