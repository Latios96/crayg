//
// Created by Jan on 28.10.2021.
//

#include "Conversions.h"
namespace crayg {

const Matrix4x4f MIRROR_Z = Matrix4x4f::scale(1, 1, -1);

Matrix4x4f Conversions::convert(const pxr::GfMatrix4d &matrix) {
    return Matrix4x4f(static_cast<float>(matrix[0][0]),
                      static_cast<float>(matrix[1][0]),
                      static_cast<float>(matrix[2][0]),
                      static_cast<float>(matrix[3][0]),
                      static_cast<float>(matrix[0][1]),
                      static_cast<float>(matrix[1][1]),
                      static_cast<float>(matrix[2][1]),
                      static_cast<float>(matrix[3][1]),
                      static_cast<float>(matrix[0][2]),
                      static_cast<float>(matrix[1][2]),
                      static_cast<float>(matrix[2][2]),
                      static_cast<float>(matrix[3][2]),
                      static_cast<float>(matrix[0][3]),
                      static_cast<float>(matrix[1][3]),
                      static_cast<float>(matrix[2][3]),
                      static_cast<float>(matrix[3][3])) * MIRROR_Z;
}
};