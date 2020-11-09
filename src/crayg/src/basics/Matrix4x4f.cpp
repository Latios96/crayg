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
