#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_

#include "Vector3f.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

class Matrix4x4f {
  public:
    Matrix4x4f();
    Matrix4x4f(const Matrix4x4f &matrix4X4F);
    Matrix4x4f(float v00, float v10, float v20, float v30, float v01, float v11, float v21, float v31, float v02,
               float v12, float v22, float v32, float v03, float v13, float v23, float v33);
    static Matrix4x4f translation(float x, float y, float z);
    static Matrix4x4f scale(float x, float y, float z);
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

    int index(int row, int column) const {
        return row * 4 + column;
    }

    float values(int row, int column) const {
        return values_[index(row, column)];
    }

    float &values(int row, int column) {
        return values_[index(row, column)];
    }

    float values_[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}; //[ROW][COLUMN]
};

}

template <> struct fmt::formatter<crayg::Matrix4x4f> : ostream_formatter {};

#endif // CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_
