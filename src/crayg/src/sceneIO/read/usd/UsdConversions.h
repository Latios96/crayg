//
// Created by Jan on 28.10.2021.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDCONVERSIONS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDCONVERSIONS_H_

#include "CraygUsdBase.h"
#include <pxr/base/gf/matrix4d.h>
#include "basics/Matrix4x4f.h"

namespace crayg {

class UsdConversions {
 public:
    static Matrix4x4f convert(const pxr::GfMatrix4d &matrix);
    static Vector3f convert(const pxr::GfVec3f &vector);
    static Vector3f convert(const pxr::GfVec3d &vector);
};

};

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDCONVERSIONS_H_