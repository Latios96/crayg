#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_TRANSFORM_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_TRANSFORM_H_

#include "Matrix4x4f.h"
#include "Ray.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

class Transform {
  public:
    Transform() {
        inverseMatrix = matrix.invert();
    }

    explicit Transform(const Matrix4x4f &matrix) : matrix(matrix), inverseMatrix(matrix.invert()) {
    }

    // explicit Transform(const Matrix4x4f &matrix, const Matrix4x4f &inverse)
    Transform(const Transform &transform) : matrix(transform.matrix), inverseMatrix(transform.inverseMatrix){};
    static Transform withPosition(const Vector3f &vector3f);
    static Transform withRotation(float x, float y, float z);
    static Transform withScale(float x, float y, float z);

    Vector3f apply(const Vector3f &vector3f) const {
        return apply(matrix, vector3f);
    }

    Vector3f applyForPoint(const Vector3f &vector3f) const {
        return applyForPoint(matrix, vector3f);
    }

    Vector3f applyForNormal(const Vector3f &vector3f) const {
        return applyForNormal(inverseMatrix, vector3f); // Note: it is correct to pass in the inverse here
    }

    Ray apply(const Ray &ray) const {
        return apply(matrix, ray);
    }

    Vector3f applyInverse(const Vector3f &vector3f) const {
        return apply(inverseMatrix, vector3f);
    }

    Vector3f applyInverseForPoint(const Vector3f &vector3f) const {
        return applyForPoint(inverseMatrix, vector3f);
    }

    Vector3f applyInverseForNormal(const Vector3f &vector3f) const {
        return applyForNormal(matrix, vector3f); // Note: it is correct to pass in the normal matrix here
    }

    Ray applyInverse(const Ray &ray) const {
        return apply(inverseMatrix, ray);
    }

    Vector3f toPosition() const {
        return {matrix.values[0][3], matrix.values[1][3], matrix.values[2][3]};
    }

    bool operator==(const Transform &rhs) const;
    bool operator!=(const Transform &rhs) const;
    Transform &operator=(const Transform &rhs);
    Transform operator*(const Transform &rhs) const;
    Transform &operator*=(const Transform &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Transform &transform);

    Matrix4x4f matrix;
    Matrix4x4f inverseMatrix;

  private:
    Vector3f apply(const Matrix4x4f &matrixToApply, const Vector3f &vector3f) const {
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

    Vector3f applyForPoint(const Matrix4x4f &matrixToApply, const Vector3f &vector3f) const {
        float x = matrixToApply.values[0][0] * vector3f.x + matrixToApply.values[0][1] * vector3f.y +
                  matrixToApply.values[0][2] * vector3f.z + matrixToApply.values[0][3];
        float y = matrixToApply.values[1][0] * vector3f.x + matrixToApply.values[1][1] * vector3f.y +
                  matrixToApply.values[1][2] * vector3f.z + matrixToApply.values[1][3];
        float z = matrixToApply.values[2][0] * vector3f.x + matrixToApply.values[2][1] * vector3f.y +
                  matrixToApply.values[2][2] * vector3f.z + matrixToApply.values[2][3];
        float w = matrixToApply.values[3][0] * vector3f.x + matrixToApply.values[3][1] * vector3f.y +
                  matrixToApply.values[3][2] * vector3f.z + matrixToApply.values[3][3];
        if (w == 0) {
            CRAYG_LOG_AND_THROW(std::runtime_error("w is 0!"));
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

    Vector3f applyForNormal(const Matrix4x4f &matrixToApply, const Vector3f &vector3f) const {
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

    Ray apply(const Matrix4x4f &matrixToApply, const Ray &ray) const {
        return {applyForPoint(matrixToApply, ray.startPoint), apply(matrixToApply, ray.direction).normalize(),
                ray.length};
    }
};

}

template <> struct fmt::formatter<crayg::Transform> : ostream_formatter {};

#endif // CRAYG_SRC_CRAYG_SRC_BASICS_TRANSFORM_H_
