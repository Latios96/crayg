//
// Created by Jan Honsbrok on 07.11.20.
//

#ifndef CRAYG_VECTOR3FNAIVEIMPL_H
#define CRAYG_VECTOR3FNAIVEIMPL_H


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

    float length() const;

    Vector3fNaiveImpl normalize() const;

    Vector3fNaiveImpl invert() const {
        return {x * -1, y * -1, z * -1};
    }

    float scalarProduct(const Vector3fNaiveImpl &otherVector) const;

    Vector3fNaiveImpl crossProduct(const Vector3fNaiveImpl &otherVector) const;

    static Vector3fNaiveImpl createInvalid();

    bool isValid();

    friend std::ostream &operator<<(std::ostream &os, const Vector3fNaiveImpl &f);

private:
    Vector3fNaiveImpl add(const Vector3fNaiveImpl &otherVector) const;

    Vector3fNaiveImpl multiplyScalar(float scalar) const;

    Vector3fNaiveImpl substract(const Vector3fNaiveImpl &otherVector) const;

};


#endif //CRAYG_VECTOR3FNAIVEIMPL_H
