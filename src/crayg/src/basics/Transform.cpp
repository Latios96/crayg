#include "Transform.h"

namespace crayg {

Transform::Transform() = default;

Transform::Transform(const Matrix4x4f &matrix) : matrix(matrix) {
}

Transform::Transform(const Transform &transform) = default;

Transform Transform::withPosition(const Vector3f &vector3f) {
    Matrix4x4f matrix4X4f;
    matrix4X4f.values[0][3] = vector3f.x;
    matrix4X4f.values[1][3] = vector3f.y;
    matrix4X4f.values[2][3] = vector3f.z;
    return Transform(matrix4X4f);
}

Vector3f Transform::applyForPoint(const Vector3f &vector3f) const {
    float x = matrix.values[0][0] * vector3f.x + matrix.values[0][1] * vector3f.y + matrix.values[0][2] * vector3f.z +
              matrix.values[0][3];
    float y = matrix.values[1][0] * vector3f.x + matrix.values[1][1] * vector3f.y + matrix.values[1][2] * vector3f.z +
              matrix.values[1][3];
    float z = matrix.values[2][0] * vector3f.x + matrix.values[2][1] * vector3f.y + matrix.values[2][2] * vector3f.z +
              matrix.values[2][3];
    float w = matrix.values[3][0] * vector3f.x + matrix.values[3][1] * vector3f.y + matrix.values[3][2] * vector3f.z +
              matrix.values[3][3];
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

Vector3f Transform::apply(const Vector3f &vector3f) const {
    const float x =
        matrix.values[0][0] * vector3f.x + matrix.values[0][1] * vector3f.y + matrix.values[0][2] * vector3f.z;
    const float y =
        matrix.values[1][0] * vector3f.x + matrix.values[1][1] * vector3f.y + matrix.values[1][2] * vector3f.z;
    const float z =
        matrix.values[2][0] * vector3f.x + matrix.values[2][1] * vector3f.y + matrix.values[2][2] * vector3f.z;

    return {
        x,
        y,
        z,
    };
}

Vector3f Transform::toPosition() const {
    return {matrix.values[0][3], matrix.values[1][3], matrix.values[2][3]};
}

bool Transform::operator==(const Transform &rhs) const {
    return matrix == rhs.matrix;
}

bool Transform::operator!=(const Transform &rhs) const {
    return !(rhs == *this);
}

Transform &Transform::operator=(const Transform &rhs) {
    matrix = rhs.matrix;
    return *this;
}

Ray Transform::apply(const Ray &ray) const {
    return {applyForPoint(ray.startPoint), apply(ray.direction), ray.length};
}

Transform Transform::withRotation(float x, float y, float z) {
    Matrix4x4f matrix4X4f;
    return Transform(matrix4X4f * Matrix4x4f::rotateX(x) * Matrix4x4f::rotateY(y) * Matrix4x4f::rotateZ(z));
}

Transform Transform::withScale(float x, float y, float z) {
    Matrix4x4f matrix4X4f;
    matrix4X4f.values[0][0] = x;
    matrix4X4f.values[1][1] = y;
    matrix4X4f.values[2][2] = z;
    return Transform(matrix4X4f);
}

Vector3f Transform::applyForNormal(const Vector3f &vector3f) const {
    const Matrix4x4f inverse = matrix.invert();
    const Matrix4x4f transpose = inverse.transpose();
    float x = transpose.values[0][0] * vector3f.x + transpose.values[0][1] * vector3f.y +
              transpose.values[0][2] * vector3f.z + transpose.values[0][3];
    float y = transpose.values[1][0] * vector3f.x + transpose.values[1][1] * vector3f.y +
              transpose.values[1][2] * vector3f.z + transpose.values[1][3];
    float z = transpose.values[2][0] * vector3f.x + transpose.values[2][1] * vector3f.y +
              transpose.values[2][2] * vector3f.z + transpose.values[2][3];

    return {
        x,
        y,
        z,
    };
}

std::ostream &operator<<(std::ostream &os, const Transform &transform) {
    os << "matrix: " << transform.matrix;
    return os;
}

}
