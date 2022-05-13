//
// Created by Jan on 28.10.2021.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_CONVERSIONS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_CONVERSIONS_H_

#define NOMINMAX
#include <pxr/base/gf/matrix4d.h>
#include <basics/Matrix4x4f.h>

namespace crayg {

class Conversions {
 public:
    static Matrix4x4f convert(const pxr::GfMatrix4d &matrix);
    static Vector3f convert(const pxr::GfVec3f &vector);
    static Vector3f convert(const pxr::GfVec3d &vector);
};

};

#endif //CRAYG_SRC_CRAYGUSD_SRC_CONVERSIONS_H_
