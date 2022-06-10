//
// Created by Jan on 28.10.2021.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDCONVERSIONS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDCONVERSIONS_H_

#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/base/gf/matrix4d.h>
#include "basics/Matrix4x4f.h"
#include "basics/Color.h"

namespace crayg {

class UsdConversions {
 public:
    static Matrix4x4f convert(const pxr::GfMatrix4d &matrix);
    static Vector3f convert(const pxr::GfVec3f &vector);
    static pxr::GfVec3f convert(const Vector3f &vector);
    static Vector3f convert(const pxr::GfVec3d &vector);
    static pxr::GfVec3f convert(const Color &color);
    static Color convertColor(const pxr::GfVec3f &color);
    static pxr::GfMatrix4d convert(const Matrix4x4f &matrix);
};

};

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDCONVERSIONS_H_