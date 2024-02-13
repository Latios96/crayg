#include "UsdConversions.h"
#include "basics/Transform.h"

namespace crayg {

const Matrix4x4f BASE_TRANSFORM_CRAYG = Matrix4x4f::scale(1, 1, -1);
const Matrix4x4f BASE_TRANSFORM_CRAYG_INVERTED = Matrix4x4f::scale(1, 1, -1).invert();

const pxr::GfMatrix4d BASE_TRANSFORM_USD = pxr::GfMatrix4d().SetScale(pxr::GfVec3d(1, 1, -1));
const pxr::GfMatrix4d BASE_TRANSFORM_USD_INVERTED = pxr::GfMatrix4d().SetScale(pxr::GfVec3d(1, 1, -1)).GetInverse();

float UsdConversions::convert(float value) {
    return value;
}

int UsdConversions::convert(int value) {
    return value;
}

Matrix4x4f UsdConversions::convert(const pxr::GfMatrix4d &matrix) {
    return BASE_TRANSFORM_CRAYG *
           Matrix4x4f(
               static_cast<float>(matrix[0][0]), static_cast<float>(matrix[1][0]), static_cast<float>(matrix[2][0]),
               static_cast<float>(matrix[3][0]), static_cast<float>(matrix[0][1]), static_cast<float>(matrix[1][1]),
               static_cast<float>(matrix[2][1]), static_cast<float>(matrix[3][1]), static_cast<float>(matrix[0][2]),
               static_cast<float>(matrix[1][2]), static_cast<float>(matrix[2][2]), static_cast<float>(matrix[3][2]),
               static_cast<float>(matrix[0][3]), static_cast<float>(matrix[1][3]), static_cast<float>(matrix[2][3]),
               static_cast<float>(matrix[3][3])) *
           BASE_TRANSFORM_CRAYG_INVERTED;
}

Vector3f UsdConversions::convert(const pxr::GfVec3f &vector) {
    return {vector[0], vector[1], -vector[2]};
}

Vector3f UsdConversions::convert(const pxr::GfVec3d &vector) {
    return {static_cast<float>(vector[0]), static_cast<float>(vector[1]), -static_cast<float>(vector[2])};
}

Vector2f UsdConversions::convert(const pxr::GfVec2f &vector) {
    return {vector[0], vector[1]};
}

Color UsdConversions::convertColor(const pxr::GfVec3f &vector) {
    return {vector[0], vector[1], vector[2]};
}

pxr::GfMatrix4d UsdConversions::convert(const Matrix4x4f &matrix) {
    return BASE_TRANSFORM_USD *
           pxr::GfMatrix4d((matrix.values(0, 0)), (matrix.values(1, 0)), (matrix.values(2, 0)), (matrix.values(3, 0)),
                           (matrix.values(0, 1)), (matrix.values(1, 1)), (matrix.values(2, 1)), (matrix.values(3, 1)),
                           (matrix.values(0, 2)), (matrix.values(1, 2)), (matrix.values(2, 2)), (matrix.values(3, 2)),
                           (matrix.values(0, 3)), (matrix.values(1, 3)), (matrix.values(2, 3)), (matrix.values(3, 3))) *
           BASE_TRANSFORM_USD_INVERTED;
}

pxr::GfVec3f UsdConversions::convert(const Vector3f &vector) {
    return {vector.x, vector.y, -vector.z};
}

pxr::GfVec3f UsdConversions::convert(const Color &color) {
    return {color.r, color.g, color.b};
}

pxr::GfVec2f UsdConversions::convert(const Vector2f &vector2f) {
    return {vector2f.x, vector2f.y};
}

pxr::GfVec2i UsdConversions::convert(const Resolution &resolution) {
    return {resolution.getWidth(), resolution.getHeight()};
}

};