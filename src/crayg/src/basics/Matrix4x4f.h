//
// Created by Jan on 09.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_

#include <ostream>
#include "Vector3f.h"
class Matrix4x4f {
 public:
    Matrix4x4f();
    Matrix4x4f(const Matrix4x4f &matrix4X4F);
    Matrix4x4f(float v00,
               float v10,
               float v20,
               float v30,
               float v01,
               float v11,
               float v21,
               float v31,
               float v02,
               float v12,
               float v22,
               float v32,
               float v03,
               float v13,
               float v23,
               float v33);
    float values[4][4] = {1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1};
    friend std::ostream &operator<<(std::ostream &os, const Matrix4x4f &f);
    bool operator==(const Matrix4x4f &rhs) const;
    bool operator!=(const Matrix4x4f &rhs) const;
    Matrix4x4f &operator=(const Matrix4x4f &rhs);
    Matrix4x4f operator*(const Matrix4x4f &vec) const;
};

#endif //CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_
