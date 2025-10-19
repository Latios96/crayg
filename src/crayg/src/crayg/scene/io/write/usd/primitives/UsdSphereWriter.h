#pragma once

#include "crayg/scene/io/write/usd/base/BaseUsdSceneObjectWriter.h"
#include "crayg/scene/primitives/Sphere.h"
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

class UsdSphereWriter : public BaseUsdSceneObjectWriter<pxr::UsdGeomSphere, Sphere> {
  public:
    UsdSphereWriter(Sphere &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache);

    pxr::UsdGeomSphere write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
};

}
