//
// Created by Jan on 28.10.2021.
//

#include "UsdConversions.h"
#include "basics/Transform.h"

namespace crayg {

const Matrix4x4f BASE_TRANSFORM = Matrix4x4f::scale(1, 1, -1);
const Matrix4x4f BASE_TRANSFORM_INVERTED = Matrix4x4f::scale(1, 1, -1).invert();

Matrix4x4f UsdConversions::convert(const pxr::GfMatrix4d &matrix) {
    return BASE_TRANSFORM * Matrix4x4f(static_cast<float>(matrix[0][0]),
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
                                       static_cast<float>(matrix[3][3])) * BASE_TRANSFORM_INVERTED;
}
Vector3f UsdConversions::convert(const pxr::GfVec3f &vector) {
    return {vector[0], vector[1], -vector[2]};
}
Vector3f UsdConversions::convert(const pxr::GfVec3d &vector) {
    return {static_cast<float>(vector[0]), static_cast<float>(vector[1]), -static_cast<float>(vector[2])};
}
Color UsdConversions::convertColor(const pxr::GfVec3f &vector) {
    return {vector[0], vector[1], vector[2]};
}

};