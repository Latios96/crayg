#include "Transform.h"
#include "utils/Exceptions.h"

namespace crayg {

Transform Transform::withPosition(const Vector3f &vector3f) {
    Matrix4x4f matrix4X4f;
    matrix4X4f.values(0, 3) = vector3f.x;
    matrix4X4f.values(1, 3) = vector3f.y;
    matrix4X4f.values(2, 3) = vector3f.z;
    return Transform(matrix4X4f);
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
    matrix4X4f.values(0, 0) = x;
    matrix4X4f.values(1, 1) = y;
    matrix4X4f.values(2, 2) = z;
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
