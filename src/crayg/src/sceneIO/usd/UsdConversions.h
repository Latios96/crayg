#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDCONVERSIONS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDCONVERSIONS_H_

#include "basics/Color.h"
#include "basics/Matrix4x4f.h"
#include "basics/Resolution.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/base/gf/matrix4d.h>
#include <pxr/base/gf/vec2f.h>
#include <pxr/base/gf/vec2i.h>

namespace crayg {

class UsdConversions {
  public:
    static float convert(float value);
    static int convert(int value);
    static Matrix4x4f convert(const pxr::GfMatrix4d &matrix);
    static Vector3f convert(const pxr::GfVec3f &vector);
    static pxr::GfVec3f convert(const Vector3f &vector);
    static Vector3f convert(const pxr::GfVec3d &vector);
    static Vector2f convert(const pxr::GfVec2f &vector);
    static pxr::GfVec3f convert(const Color &color);
    static pxr::GfVec2f convert(const Vector2f &vector);
    static Color convertColor(const pxr::GfVec3f &color);
    static pxr::GfMatrix4d convert(const Matrix4x4f &matrix);
    static pxr::GfVec2i convert(const Resolution &resolution);
};

};

#endif // CRAYG_SRC_CRAYGUSD_SRC_USDCONVERSIONS_H_
