//
// Created by Jan on 09.11.2020.
//

#include <fmt/format.h>
#include "Matrix4x4f.h"

std::ostream &operator<<(std::ostream &os, const Matrix4x4f &matrix4X4F) {
    os << fmt::format("Matrix4x4f(values={{{} {} {} {}, {} {} {} {}, {} {} {} {}, {} {} {} {}}})",
                      matrix4X4F.values[0][0],
                      matrix4X4F.values[0][1],
                      matrix4X4F.values[0][2],
                      matrix4X4F.values[0][3],
                      matrix4X4F.values[1][0],
                      matrix4X4F.values[1][1],
                      matrix4X4F.values[1][2],
                      matrix4X4F.values[1][3],
                      matrix4X4F.values[2][0],
                      matrix4X4F.values[2][1],
                      matrix4X4F.values[2][2],
                      matrix4X4F.values[2][3],
                      matrix4X4F.values[3][0],
                      matrix4X4F.values[3][1],
                      matrix4X4F.values[3][2],
                      matrix4X4F.values[3][3]);
    return os;
}

Matrix4x4f::Matrix4x4f(float v00,
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
                       float v33) {
    values[0][0] = v00;
    values[0][1] = v10;
    values[0][2] = v20;
    values[0][3] = v30;
    values[1][0] = v01;
    values[1][1] = v11;
    values[1][2] = v21;
    values[1][3] = v31;
    values[2][0] = v02;
    values[2][1] = v12;
    values[2][2] = v22;
    values[2][3] = v32;
    values[3][0] = v03;
    values[3][1] = v13;
    values[3][2] = v23;
    values[3][3] = v33;
}
Matrix4x4f Matrix4x4f::operator*(const Matrix4x4f &vec) const {
    Matrix4x4f r;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            r.values[i][j] =
                values[i][0] * vec.values[0][j] + values[i][1] * vec.values[1][j] + values[i][2] * vec.values[2][j]
                    + values[i][3] * vec.values[3][j];
        }
    }
    return r;
}
bool Matrix4x4f::operator==(const Matrix4x4f &rhs) const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (values[i][j] != rhs.values[i][j]) {
                return false;
            }
        }
    }
    return true;
}
bool Matrix4x4f::operator!=(const Matrix4x4f &rhs) const {
    return !(rhs == *this);
}
Matrix4x4f::Matrix4x4f(const Matrix4x4f &matrix4X4F) {
    memcpy(values, matrix4X4F.values, sizeof(float) * 16);
}

Matrix4x4f::Matrix4x4f() = default;
