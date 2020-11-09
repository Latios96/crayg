//
// Created by Jan on 09.11.2020.
//


#include "Transform.h"
Transform::Transform() = default;
Transform::Transform(const Matrix4x4f &matrix) : matrix(matrix) {}

Transform Transform::fromPosition(const Vector3f &vector3f) {
    Matrix4x4f matrix4X4f;
    matrix4X4f.values[0][3] = vector3f.x;
    matrix4X4f.values[1][3] = vector3f.y;
    matrix4X4f.values[2][3] = vector3f.z;
    return Transform(matrix4X4f);
}

Vector3f Transform::apply(const Vector3f &vector3f) const {
    float x = matrix.values[0][0] * vector3f.x + matrix.values[0][1] * vector3f.y
        + matrix.values[0][2] * vector3f.z + matrix.values[0][3];
    float y = matrix.values[1][0] * vector3f.x + matrix.values[1][1] * vector3f.y
        + matrix.values[1][2] * vector3f.z + matrix.values[1][3];
    float z = matrix.values[2][0] * vector3f.x + matrix.values[2][1] * vector3f.y
        + matrix.values[2][2] * vector3f.z + matrix.values[2][3];
    float w = matrix.values[3][0] * vector3f.x + matrix.values[3][1] * vector3f.y
        + matrix.values[3][2] * vector3f.z + matrix.values[3][3];
    if (w == 0) {
        throw std::runtime_error("w is 0!");
    }
    if (w == 1) {
        return {
            x,
            y,
            z,
        };
    }
    return {
        x / w,
        y / w,
        z / w,
    };

}

Vector3f Transform::toPosition() const {
    return {matrix.values[0][3], matrix.values[1][3], matrix.values[2][3]};
}

