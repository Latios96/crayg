//
// Created by Jan on 09.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_TRANSFORM_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_TRANSFORM_H_

#include "Matrix4x4f.h"

class Transform {
 public:
    Transform();
    explicit Transform(const Matrix4x4f &matrix);
    Transform(const Transform &transform);
    static Transform fromPosition(const Vector3f &vector3f);
    // normal
    // transform rotate xyz
    // scale xyz
    Vector3f apply(const Vector3f &vector3f) const;
    Vector3f toPosition() const;

    bool operator==(const Transform &rhs) const;
    bool operator!=(const Transform &rhs) const;
    Transform &operator=(const Transform &rhs);

    Matrix4x4f matrix;
};

#endif //CRAYG_SRC_CRAYG_SRC_BASICS_TRANSFORM_H_
