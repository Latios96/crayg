//
// Created by Jan on 09.11.2020.
//
#define _USE_MATH_DEFINES
#include <cmath>
#include <fmt/format.h>
#include <iostream>
#include "Matrix4x4f.h"

namespace crayg {

std::ostream &operator<<(std::ostream &os, const Matrix4x4f &matrix4X4F) {
    os << fmt::format(
        "Matrix4x4f(values={{\n{:.2f} {:.2f} {:.2f} {:.2f}\n{:.2f} {:.2f} {:.2f} {:.2f}\n{:.2f} {:.2f} {:.2f} {:.2f}\n{:.2f} {:.2f} {:.2f} {:.2f}}})",
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
Matrix4x4f &Matrix4x4f::operator=(const Matrix4x4f &rhs) {
    memcpy(values, rhs.values, sizeof(float) * 16);
    return *this;
}
Matrix4x4f Matrix4x4f::invert() const {
    Matrix4x4f result = *this;

    for (int columnIndex = 0; columnIndex < 4; columnIndex++) {
        float factor = 1.0f / result.values[columnIndex][columnIndex];

        // scale elements in column, so required element is 1
        result.values[columnIndex][columnIndex] = 1; // set to one, so we dont have to care about that in the loop
        for (int r = 0; r < 4; r++) {
            result.values[columnIndex][r] = result.values[columnIndex][r] * factor;
        }
        // substract other rows to zero out
        for (int rowIndex = 0; rowIndex < 4; rowIndex++) {
            if (rowIndex != columnIndex) {
                float rowFactor = result.values[rowIndex][columnIndex];
                result.values[rowIndex][columnIndex] = 0; // set to zero, so we dont have to care about that in the loop
                for (int c = 0; c < 4; c++) {
                    result.values[rowIndex][c] -= result.values[columnIndex][c] * rowFactor;
                }
            }
        }
    }

    return result;
}
bool Matrix4x4f::isEqualTo(const Matrix4x4f &rhs) const {
    return *this == rhs;

}
bool Matrix4x4f::isEqualTo(const Matrix4x4f &rhs, float epsilon) const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float difference = values[i][j] - rhs.values[i][j];
            float absDifference = std::abs(difference);
            if (absDifference > epsilon) {
                return false;
            }
        }
    }
    return true;
}
Matrix4x4f Matrix4x4f::rotateX(float angleInDegrees) {
    float angleInRadians = (angleInDegrees * M_PI / 180.0f);
    return Matrix4x4f(1, 0, 0, 0,
                      0, std::cos(angleInRadians), -std::sin(angleInRadians), 0,
                      0, std::sin(angleInRadians), std::cos(angleInRadians), 0,
                      0, 0, 0, 1);
}
Matrix4x4f Matrix4x4f::rotateY(float angleInDegrees) {
    float angleInRadians = (angleInDegrees * M_PI / 180.0f);
    return Matrix4x4f(std::cos(angleInRadians), 0, std::sin(angleInRadians), 0,
                      0, 1, 0, 0,
                      -std::sin(angleInRadians), 0, std::cos(angleInRadians), 0,
                      0, 0, 0, 1);
}
Matrix4x4f Matrix4x4f::rotateZ(float angleInDegrees) {
    float angleInRadians = (angleInDegrees * M_PI / 180.0f);
    return Matrix4x4f(std::cos(angleInRadians), -std::sin(angleInRadians), 0, 0,
                      std::sin(angleInRadians), std::cos(angleInRadians), 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1);
}
Matrix4x4f Matrix4x4f::transpose() const {
    return Matrix4x4f(values[0][0],
                      values[1][0],
                      values[2][0],
                      values[3][0],
                      values[0][1],
                      values[1][1],
                      values[2][1],
                      values[3][1],
                      values[0][2],
                      values[1][2],
                      values[2][2],
                      values[3][2],
                      values[0][3],
                      values[1][3],
                      values[2][3],
                      values[3][3]);
}
Matrix4x4f Matrix4x4f::translation(float x, float y, float z) {
    Matrix4x4f matrix4X4f;
    matrix4X4f.values[0][3] = x;
    matrix4X4f.values[1][3] = y;
    matrix4X4f.values[2][3] = z;
    return matrix4X4f;
}
Matrix4x4f Matrix4x4f::scale(float x, float y, float z) {
    Matrix4x4f matrix4X4f;
    matrix4X4f.values[0][0] = x;
    matrix4X4f.values[1][1] = y;
    matrix4X4f.values[2][2] = z;
    return matrix4X4f;
}

Matrix4x4f::Matrix4x4f() = default;

}