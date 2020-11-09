//
// Created by Jan on 09.11.2020.
//

#include <fmt/format.h>
#include "Matrix4x4f.h"

std::ostream &operator<<(std::ostream &os, const Matrix4x4f &matrix4X4F) {
    os << fmt::format("Matrix4x4f(values={{{} {} {} {}, {} {} {} {}, {} {} {} {}, {} {} {} {}}})",
                      matrix4X4F.values[0][0],
                      matrix4X4F.values[1][0],
                      matrix4X4F.values[2][0],
                      matrix4X4F.values[3][0],
                      matrix4X4F.values[0][1],
                      matrix4X4F.values[1][1],
                      matrix4X4F.values[2][1],
                      matrix4X4F.values[3][1],
                      matrix4X4F.values[0][2],
                      matrix4X4F.values[1][2],
                      matrix4X4F.values[2][2],
                      matrix4X4F.values[3][2],
                      matrix4X4F.values[0][3],
                      matrix4X4F.values[1][3],
                      matrix4X4F.values[2][3],
                      matrix4X4F.values[3][3]);
    return os;
}
Matrix4x4f Matrix4x4f::operator*(const Vector3f &vec) const {
    return Matrix4x4f();
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
    values[1][0] = v10;
    values[2][0] = v20;
    values[3][0] = v30;
    values[0][1] = v01;
    values[1][1] = v11;
    values[2][1] = v21;
    values[3][1] = v31;
    values[0][2] = v02;
    values[1][2] = v12;
    values[2][2] = v22;
    values[3][2] = v32;
    values[0][3] = v03;
    values[1][3] = v13;
    values[2][3] = v23;
    values[3][3] = v33;
}

Matrix4x4f::Matrix4x4f() = default;
