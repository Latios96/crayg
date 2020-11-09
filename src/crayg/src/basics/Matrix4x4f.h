//
// Created by Jan on 09.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_

#include <ostream>
class Matrix4x4f {
 public:
    const float values[4][4] = {{1, 0, 0, 0},
                          {0, 1, 0, 0},
                          {0, 0, 1, 0},
                          {0, 0, 0, 1}};
    friend std::ostream &operator<<(std::ostream &os, const Matrix4x4f &f);
};

#endif //CRAYG_SRC_CRAYG_SRC_BASICS_MATRIX4X4F_H_
