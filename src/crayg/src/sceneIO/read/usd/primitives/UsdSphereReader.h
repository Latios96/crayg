#pragma once

#include "scene/primitives/Sphere.h"
#include "sceneIO/read/usd/base/BaseUsdImageableReader.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

class UsdSphereReader : public BaseUsdImageableReader<pxr::UsdGeomSphere, Sphere> {
  public:
    UsdSphereReader(const pxr::UsdGeomSphere &usdPrim, UsdMaterialReadCache &usdMaterialTranslationCache);
    std::shared_ptr<Sphere> read() override;

  protected:
    std::string getTranslatedType() override;
};

}
