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
    // point aka vec3
    // normal
    // transform xyz
    // transform rotate xyz
    // scale xyz
    Vector3f apply(const Vector3f &vector3f);

    const Matrix4x4f matrix;
};

#endif //CRAYG_SRC_CRAYG_SRC_BASICS_TRANSFORM_H_
