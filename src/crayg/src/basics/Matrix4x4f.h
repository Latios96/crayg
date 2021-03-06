//
// Created by Jan on 09.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_

#include <ostream>
#include "Vector3f.h"

namespace crayg {

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

    static Matrix4x4f rotateX(float angleInDegrees);
    static Matrix4x4f rotateY(float angleInDegrees);
    static Matrix4x4f rotateZ(float angleInDegrees);

    friend std::ostream &operator<<(std::ostream &os, const Matrix4x4f &f);
    bool operator==(const Matrix4x4f &rhs) const;
    bool operator!=(const Matrix4x4f &rhs) const;
    bool isEqualTo(const Matrix4x4f &rhs) const;
    bool isEqualTo(const Matrix4x4f &rhs, float epsilon) const;
    Matrix4x4f &operator=(const Matrix4x4f &rhs);
    Matrix4x4f operator*(const Matrix4x4f &vec) const;
    Matrix4x4f invert() const;
    Matrix4x4f transpose() const;

    float values[4][4] = {1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1}; //[ROW][COLUMN]
};

}
#endif //CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_
