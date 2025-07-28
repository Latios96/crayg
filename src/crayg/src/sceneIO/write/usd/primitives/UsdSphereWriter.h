#pragma once

#include "scene/primitives/Sphere.h"
#include "sceneIO/write/usd/base/BaseUsdSceneObjectWriter.h"
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

class UsdSphereWriter : public BaseUsdSceneObjectWriter<pxr::UsdGeomSphere, Sphere> {
  public:
    UsdSphereWriter(Sphere &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache);

    pxr::UsdGeomSphere write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
};

}
