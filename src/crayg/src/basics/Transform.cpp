#include "Transform.h"

namespace crayg {

Transform::Transform() {
    inverseMatrix = matrix.invert();
}

Transform::Transform(const Matrix4x4f &matrix) : matrix(matrix), inverseMatrix(matrix.invert()) {
}

Transform::Transform(const Transform &transform) : matrix(transform.matrix), inverseMatrix(transform.inverseMatrix){};

Transform Transform::withPosition(const Vector3f &vector3f) {
    Matrix4x4f matrix4X4f;
    matrix4X4f.values[0][3] = vector3f.x;
    matrix4X4f.values[1][3] = vector3f.y;
    matrix4X4f.values[2][3] = vector3f.z;
    return Transform(matrix4X4f);
}

Vector3f Transform::apply(const Vector3f &vector3f) const {
    return apply(matrix, vector3f);
}

Vector3f Transform::applyForPoint(const Vector3f &vector3f) const {
    return applyForPoint(matrix, vector3f);
}

Vector3f Transform::applyForNormal(const Vector3f &vector3f) const {
    return applyForNormal(inverseMatrix, vector3f); // Note: it is correct to pass in the inverse here
}

Ray Transform::apply(const Ray &ray) const {
    return apply(matrix, ray);
}

Vector3f Transform::applyInverse(const Vector3f &vector3f) const {
    return apply(inverseMatrix, vector3f);
}

Vector3f Transform::applyInverseForPoint(const Vector3f &vector3f) const {
    return applyForPoint(inverseMatrix, vector3f);
}

Vector3f Transform::applyInverseForNormal(const Vector3f &vector3f) const {
    return applyForNormal(matrix, vector3f); // Note: it is correct to pass in the normal matrix here
}

Ray Transform::applyInverse(const Ray &ray) const {
    return apply(inverseMatrix, ray);
}

Vector3f Transform::applyForPoint(const Matrix4x4f &matrixToApply, const Vector3f &vector3f) const {
    float x = matrixToApply.values[0][0] * vector3f.x + matrixToApply.values[0][1] * vector3f.y +
              matrixToApply.values[0][2] * vector3f.z + matrixToApply.values[0][3];
    float y = matrixToApply.values[1][0] * vector3f.x + matrixToApply.values[1][1] * vector3f.y +
              matrixToApply.values[1][2] * vector3f.z + matrixToApply.values[1][3];
    float z = matrixToApply.values[2][0] * vector3f.x + matrixToApply.values[2][1] * vector3f.y +
              matrixToApply.values[2][2] * vector3f.z + matrixToApply.values[2][3];
    float w = matrixToApply.values[3][0] * vector3f.x + matrixToApply.values[3][1] * vector3f.y +
              matrixToApply.values[3][2] * vector3f.z + matrixToApply.values[3][3];
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

Vector3f Transform::apply(const Matrix4x4f &matrixToApply, const Vector3f &vector3f) const {
    const float x = matrixToApply.values[0][0] * vector3f.x + matrixToApply.values[0][1] * vector3f.y +
                    matrixToApply.values[0][2] * vector3f.z;
    const float y = matrixToApply.values[1][0] * vector3f.x + matrixToApply.values[1][1] * vector3f.y +
                    matrixToApply.values[1][2] * vector3f.z;
    const float z = matrixToApply.values[2][0] * vector3f.x + matrixToApply.values[2][1] * vector3f.y +
                    matrixToApply.values[2][2] * vector3f.z;

    return {
        x,
        y,
        z,
    };
}

Vector3f Transform::applyForNormal(const Matrix4x4f &matrixToApply, const Vector3f &vector3f) const {
    const Matrix4x4f transpose = matrixToApply.transpose();
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

Ray Transform::apply(const Matrix4x4f &matrixToApply, const Ray &ray) const {
    return {applyForPoint(matrixToApply, ray.startPoint), apply(matrixToApply, ray.direction).normalize(), ray.length};
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
    inverseMatrix = matrix.invert();
    return *this;
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

std::ostream &operator<<(std::ostream &os, const Transform &transform) {
    os << "matrix: " << transform.matrix;
    return os;
}

Transform Transform::operator*(const Transform &rhs) const {
    return Transform(matrix * rhs.matrix);
}

Transform &Transform::operator*=(const Transform &rhs) {
    matrix = matrix * rhs.matrix;
    inverseMatrix = matrix.invert();
    return *this;
}

}
