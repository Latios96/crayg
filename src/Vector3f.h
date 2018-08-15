//
// Created by jan on 15.08.18.
//

#ifndef CRAYG_VECTOR3F_H
#define CRAYG_VECTOR3F_H


#include <cmath>

class Vector3f {
public:
    float x, y, z;

    /**
    Creates a new Vector and initialised x,y,z to 0
    */
    Vector3f();

    Vector3f(float _x, float _y, float _z);

    // TODO use operator overloading
    Vector3f add(const Vector3f &otherVector);

    Vector3f substract(const Vector3f &otherVector);

    Vector3f multiplyScalar(float scalar);

    float length();

    Vector3f normalize();

    Vector3f invert() {
        return {x*-1, y*-1, z*-1};
    }

    Vector3f crossProduct(const Vector3f &otherVector);

};


#endif //CRAYG_VECTOR3F_H
